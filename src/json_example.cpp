#include <json/json.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <string>
#include <fstream>

/**
 * @brief Example demonstrating jsoncpp and fmt libraries
 * 
 * This example shows how to:
 * - Create JSON objects using jsoncpp
 * - Parse JSON from strings
 * - Pretty print using fmt with colors
 */
void jsonExample() {
    // Create a JSON object
    Json::Value root;
    root["name"] = "C++ SDLC Demo";
    root["version"] = "1.0.0";
    root["description"] = "Sample application using vcpkg private registry";
    
    // Add an array
    Json::Value dependencies(Json::arrayValue);
    dependencies.append("fmt");
    dependencies.append("jsoncpp");
    dependencies.append("gtest");
    root["dependencies"] = dependencies;
    
    // Add nested object
    Json::Value config;
    config["debug"] = true;
    config["log_level"] = "info";
    config["max_threads"] = 4;
    root["config"] = config;
    
    // Pretty print the JSON using fmt
    fmt::print(fmt::fg(fmt::color::cyan), "\n=== JSON Object Created ===\n");
    
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  ";
    std::string jsonString = Json::writeString(builder, root);
    
    fmt::print("{}\n", jsonString);
    
    // Parse JSON from string
    const std::string jsonInput = R"({
        "user": "developer",
        "score": 95,
        "active": true
    })";
    
    Json::Value parsed;
    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    std::istringstream stream(jsonInput);
    
    if (Json::parseFromStream(readerBuilder, stream, &parsed, &errors)) {
        fmt::print(fmt::fg(fmt::color::green), "\n✓ Successfully parsed JSON\n");
        fmt::print("User: {}\n", parsed["user"].asString());
        fmt::print("Score: {}\n", parsed["score"].asInt());
        fmt::print("Active: {}\n", parsed["active"].asBool());
    } else {
        fmt::print(fmt::fg(fmt::color::red), "✗ Failed to parse JSON: {}\n", errors);
    }
    
    // Demonstrate fmt formatting features
    fmt::print(fmt::fg(fmt::color::yellow) | fmt::emphasis::bold, 
               "\n=== fmt Library Features ===\n");
    
    fmt::print("Formatted number: {:>10.2f}\n", 3.14159);
    fmt::print("Hexadecimal: {:#x}\n", 255);
    fmt::print("Binary: {:#b}\n", 42);
    fmt::print(fmt::fg(fmt::color::magenta), "Colored text support!\n");
}

int main() {
    try {
        jsonExample();
        return 0;
    } catch (const std::exception& e) {
        fmt::print(fmt::fg(fmt::color::red), "Error: {}\n", e.what());
        return 1;
    }
}
