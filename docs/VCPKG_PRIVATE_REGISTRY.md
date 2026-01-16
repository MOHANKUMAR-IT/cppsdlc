# vcpkg Private Registry Setup Guide

This document explains how to set up and use a private vcpkg registry for your organization.

## Overview

vcpkg supports multiple types of registries:
1. **Git-based registries** - Host custom ports in a Git repository
2. **Filesystem registries** - Local directory with custom ports
3. **Artifact registries** - Binary package hosting (Azure Artifacts, GitHub Packages)

## Setting Up a Private Git Registry

### 1. Create a Registry Repository

```bash
# Create a new repository for your custom vcpkg registry
git init vcpkg-registry
cd vcpkg-registry

# Create the required directory structure
mkdir -p ports
mkdir -p versions

# Create versions baseline file
cat > versions/baseline.json << EOF
{
  "default": {}
}
EOF

# Create port-versions directory
mkdir -p versions/port-versions
```

### 2. Add Custom Packages

Create a custom port (example: `custom-logger`):

```bash
mkdir -p ports/custom-logger

cat > ports/custom-logger/vcpkg.json << EOF
{
  "name": "custom-logger",
  "version": "1.0.0",
  "description": "Custom logging library for internal use",
  "homepage": "https://github.com/MOHANKUMAR-IT/custom-logger",
  "license": "Proprietary"
}
EOF

cat > ports/custom-logger/portfile.cmake << EOF
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO MOHANKUMAR-IT/custom-logger
    REF v1.0.0
    SHA512 <compute-sha512-hash>
    HEAD_REF main
)

vcpkg_cmake_configure(
    SOURCE_PATH "\${SOURCE_PATH}"
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup()
vcpkg_copy_pdbs()

file(REMOVE_RECURSE "\${CURRENT_PACKAGES_DIR}/debug/include")
file(INSTALL "\${SOURCE_PATH}/LICENSE" DESTINATION "\${CURRENT_PACKAGES_DIR}/share/\${PORT}" RENAME copyright)
EOF
```

### 3. Update Version Database

```bash
# Add version information
cat > versions/port-versions/c-/custom-logger.json << EOF
{
  "versions": [
    {
      "version": "1.0.0",
      "git-tree": "$(git rev-parse HEAD:ports/custom-logger)"
    }
  ]
}
EOF

# Update baseline
cat > versions/baseline.json << EOF
{
  "default": {
    "custom-logger": {
      "baseline": "1.0.0",
      "port-version": 0
    }
  }
}
EOF

# Commit and push
git add .
git commit -m "Add custom-logger v1.0.0"
git push
```

## Configuring Your Project

### Option A: Allow Public Registry (Default)

For organizations that allow public packages:

```json
{
  "default-registry": {
    "kind": "git",
    "repository": "https://github.com/microsoft/vcpkg",
    "baseline": "latest"
  },
  "registries": [
    {
      "kind": "git",
      "repository": "https://github.com/MOHANKUMAR-IT/vcpkg-registry",
      "baseline": "abc123def456...",
      "packages": ["custom-logger", "custom-*"]
    }
  ]
}
```

### Option B: Private Registry Only (Restricted Access)

For organizations that want to control all third-party dependencies:

```json
{
  "default-registry": {
    "kind": "git",
    "repository": "https://github.com/MOHANKUMAR-IT/vcpkg-registry",
    "baseline": "abc123def456..."
  },
  "registries": []
}
```

**Important**: When using private registry only, you must mirror all required packages from the public vcpkg registry into your private registry. See "Mirroring Public Packages" section below.

### Using Private Packages

In your `vcpkg.json`:

```json
{
  "dependencies": [
    "fmt",
    "custom-logger"
  ]
}
```

## Authentication for Private Repositories

### GitHub Personal Access Token

```bash
# Set environment variable
export VCPKG_BINARY_SOURCES="clear;nuget,GitHub,readwrite"

# Configure Git credentials
git config --global credential.helper store
echo "https://username:TOKEN@github.com" > ~/.git-credentials
```

### Azure DevOps

```bash
# Set up credential provider
export VCPKG_BINARY_SOURCES="clear;nuget,https://pkgs.dev.azure.com/yourorg/_packaging/yourfeed/nuget/v3/index.json,readwrite"
```

## Binary Caching

Enable binary caching for faster builds:

```bash
# Local filesystem cache
export VCPKG_BINARY_SOURCES="clear;files,/path/to/cache,readwrite"

# Azure Blob Storage
export VCPKG_BINARY_SOURCES="clear;x-azblob,https://account.blob.core.windows.net/container,readwrite"

# NuGet feed (Azure Artifacts, GitHub Packages)
export VCPKG_BINARY_SOURCES="clear;nuget,https://nuget.pkg.github.com/MOHANKUMAR-IT/index.json,readwrite"
```

## Mirroring Public Packages to Private Registry

For organizations requiring controlled access to all dependencies, mirror approved public packages to your private registry.

### Process Overview

1. **Review Request**: Team member requests a package
2. **Security Review**: Security team reviews package
3. **Approval**: Package approved for internal use
4. **Mirror**: Copy port to private registry
5. **Deploy**: Developers can now use the package

### Step-by-Step: Adding jsoncpp

#### 1. Copy Port from Public vcpkg

```bash
# Clone public vcpkg if you don't have it
git clone https://github.com/microsoft/vcpkg.git /tmp/vcpkg-public

# Navigate to your private registry
cd vcpkg-registry

# Copy the jsoncpp port
cp -r /tmp/vcpkg-public/ports/jsoncpp ./ports/

# On Windows (PowerShell):
# Copy-Item -Recurse C:\path\to\vcpkg\ports\jsoncpp .\ports\
```

#### 2. Add to Version Database

```bash
# Commit the port first to get git-tree hash
git add ports/jsoncpp
git commit -m "Add jsoncpp port"

# Get the git-tree hash
TREE_HASH=$(git rev-parse HEAD:ports/jsoncpp)

# Create version entry (jsoncpp starts with 'j')
mkdir -p versions/port-versions/j-

cat > versions/port-versions/j-/jsoncpp.json << EOF
{
  "versions": [
    {
      "version": "1.9.5",
      "git-tree": "$TREE_HASH"
    }
  ]
}
EOF
```

#### 3. Update Baseline

Edit `versions/baseline.json` to add jsoncpp:

```json
{
  "default": {
    "custom-logger": {
      "baseline": "1.0.0",
      "port-version": 0
    },
    "jsoncpp": {
      "baseline": "1.9.5",
      "port-version": 0
    }
  }
}
```

#### 4. Commit and Push

```bash
git add versions/
git commit -m "Add jsoncpp to version database"
git push origin main
```

#### 5. Update Baseline Hash in Projects

Get the commit hash for the baseline:

```bash
git rev-parse HEAD
```

Update all projects' `vcpkg-configuration.json` with the new baseline commit hash.

### Automated Mirroring Script

Create a script to automate the process:

```bash
#!/bin/bash
# mirror-package.sh - Mirror a package from public vcpkg

PACKAGE_NAME=$1
PUBLIC_VCPKG_PATH=$2
PRIVATE_REGISTRY_PATH=$3

if [ -z "$PACKAGE_NAME" ] || [ -z "$PUBLIC_VCPKG_PATH" ] || [ -z "$PRIVATE_REGISTRY_PATH" ]; then
    echo "Usage: $0 <package-name> <public-vcpkg-path> <private-registry-path>"
    exit 1
fi

cd "$PRIVATE_REGISTRY_PATH"

# Copy port
echo "Copying port $PACKAGE_NAME..."
cp -r "$PUBLIC_VCPKG_PATH/ports/$PACKAGE_NAME" ./ports/

# Commit to get git-tree hash
git add "ports/$PACKAGE_NAME"
git commit -m "Add $PACKAGE_NAME port"

# Get git-tree hash
TREE_HASH=$(git rev-parse HEAD:ports/$PACKAGE_NAME)

# Determine version (read from vcpkg.json)
VERSION=$(jq -r '.version // .["version-string"]' "ports/$PACKAGE_NAME/vcpkg.json")

# Get first letter for directory structure
FIRST_LETTER=$(echo "$PACKAGE_NAME" | cut -c1)
VERSION_DIR="versions/port-versions/${FIRST_LETTER}-"

# Create version entry
mkdir -p "$VERSION_DIR"
cat > "$VERSION_DIR/$PACKAGE_NAME.json" << EOF
{
  "versions": [
    {
      "version": "$VERSION",
      "git-tree": "$TREE_HASH"
    }
  ]
}
EOF

echo "Package $PACKAGE_NAME mirrored successfully!"
echo "Remember to update versions/baseline.json manually"
```

Usage:
```bash
./mirror-package.sh jsoncpp /path/to/public-vcpkg /path/to/private-registry
```

### Governance Process

#### Package Request Template

Create a standardized request form:

```yaml
# package-request.yml
package_name: jsoncpp
version: 1.9.5
justification: |
  Needed for JSON parsing in Project X
business_owner: john.doe@company.com
security_review: pending
license: MIT
approval_status: pending
approved_by: null
approved_date: null
```

#### Review Checklist

- [ ] License compatible with company policy
- [ ] Known security vulnerabilities checked (CVE database)
- [ ] Source code review completed
- [ ] Build process verified
- [ ] No conflicting dependencies
- [ ] Documentation reviewed
- [ ] Business justification approved
- [ ] Technical approval obtained

#### Approval Workflow

1. Developer submits package request
2. Automated security scan runs
3. License compliance check
4. Manual security review (if needed)
5. Approval/rejection decision
6. If approved, mirror to private registry
7. Notify requester

### Maintaining Mirrored Packages

#### Updating Packages

When updating to a new version:

```bash
# Pull latest from public vcpkg
cd /tmp/vcpkg-public
git pull

# Copy updated port
cp -r /tmp/vcpkg-public/ports/jsoncpp /path/to/private-registry/ports/

# Update version database
cd /path/to/private-registry
git add ports/jsoncpp
git commit -m "Update jsoncpp to version X.Y.Z"

TREE_HASH=$(git rev-parse HEAD:ports/jsoncpp)

# Append to version history
jq '.versions += [{"version": "X.Y.Z", "git-tree": "'$TREE_HASH'"}]' \
  versions/port-versions/j-/jsoncpp.json > tmp.json
mv tmp.json versions/port-versions/j-/jsoncpp.json

# Update baseline
git add versions/
git commit -m "Update jsoncpp version database"
git push
```

#### Version Pinning

Pin specific versions in your projects:

```json
{
  "dependencies": [
    {
      "name": "jsoncpp",
      "version>=": "1.9.5"
    }
  ],
  "overrides": [
    {
      "name": "jsoncpp",
      "version": "1.9.5"
    }
  ]
}
```

## Best Practices

1. **Version Control**: Always version your custom ports
2. **Baseline Management**: Update baselines carefully
3. **Documentation**: Document custom packages thoroughly
4. **Testing**: Test ports in CI/CD before releasing
5. **Security**: Use authentication for private registries
6. **Binary Caching**: Enable for faster builds
7. **Mirror Public Ports**: Mirror all approved public dependencies
8. **Governance**: Implement approval workflow for new packages
9. **Regular Updates**: Keep mirrored packages updated
10. **Audit Trail**: Maintain records of all package approvals

## Overlay Ports (Alternative)

For quick prototyping or patches, use overlay ports:

```
project/
├── custom-ports/
│   └── custom-logger/
│       ├── vcpkg.json
│       └── portfile.cmake
└── vcpkg-configuration.json
```

In `vcpkg-configuration.json`:
```json
{
  "overlay-ports": ["./custom-ports"]
}
```

## Troubleshooting

### Registry Not Found
- Verify Git repository URL
- Check authentication credentials
- Ensure baseline commit hash is correct

### Package Not Installing
- Validate portfile.cmake syntax
- Check version database consistency
- Review package name patterns in registry configuration

### Binary Cache Issues
- Verify storage credentials
- Check network connectivity
- Ensure proper read/write permissions

## Additional Resources

- [vcpkg Registries Documentation](https://learn.microsoft.com/vcpkg/users/registries)
- [Creating Custom Ports](https://learn.microsoft.com/vcpkg/examples/manifest-mode-cmake)
- [Binary Caching](https://learn.microsoft.com/vcpkg/users/binarycaching)
