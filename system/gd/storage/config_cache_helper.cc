/*
 * Copyright 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "storage/config_cache_helper.h"
#include "common/strings.h"

namespace bluetooth {
namespace storage {

void ConfigCacheHelper::SetBool(const std::string& section, const std::string& property, bool value) {
  config_cache_.SetProperty(section, property, value ? "true" : "false");
}

std::optional<bool> ConfigCacheHelper::GetBool(const std::string& section, const std::string& property) const {
  auto value_str = config_cache_.GetProperty(section, property);
  if (!value_str) {
    return std::nullopt;
  }
  if (*value_str == "true") {
    return true;
  } else if (*value_str == "false") {
    return false;
  } else {
    return std::nullopt;
  }
}

void ConfigCacheHelper::SetUint64(const std::string& section, const std::string& property, uint64_t value) {
  config_cache_.SetProperty(section, property, std::to_string(value));
}

std::optional<uint64_t> ConfigCacheHelper::GetUint64(const std::string& section, const std::string& property) const {
  auto value_str = config_cache_.GetProperty(section, property);
  if (!value_str) {
    return std::nullopt;
  }
  std::size_t pos = 0;
  uint64_t value = std::stoull(*value_str, &pos);
  if (pos != value_str->size()) {
    return std::nullopt;
  }
  return value;
}

void ConfigCacheHelper::SetInt(const std::string& section, const std::string& property, int value) {
  config_cache_.SetProperty(section, property, std::to_string(value));
}

std::optional<int> ConfigCacheHelper::GetInt(const std::string& section, const std::string& property) const {
  auto value_str = config_cache_.GetProperty(section, property);
  if (!value_str) {
    return std::nullopt;
  }
  std::size_t pos = 0;
  int value = std::stoi(*value_str, &pos);
  if (pos != value_str->size()) {
    return std::nullopt;
  }
  return value;
}

void ConfigCacheHelper::SetBin(
    const std::string& section, const std::string& property, const std::vector<uint8_t>& value) {
  config_cache_.SetProperty(section, property, common::ToHexString(value));
}

std::optional<std::vector<uint8_t>> ConfigCacheHelper::GetBin(
    const std::string& section, const std::string& property) const {
  auto value_str = config_cache_.GetProperty(section, property);
  if (!value_str) {
    return std::nullopt;
  }
  auto value = common::FromHexString(*value_str);
  if (!value) {
    LOG_WARN("value_str cannot be parsed to std::vector<uint8_t>");
  }
  return value;
}

}  // namespace storage
}  // namespace bluetooth