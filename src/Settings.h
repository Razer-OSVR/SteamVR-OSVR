/** @file
    @brief Header

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com>

*/

// Copyright 2016 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_Settings_h_GUID_3C3922D1_0C13_4E57_9EE4_85E6F23FFC67
#define INCLUDED_Settings_h_GUID_3C3922D1_0C13_4E57_9EE4_85E6F23FFC67

// Internal Includes
#include "identity.h"

// Library/third-party includes
#include <openvr_driver.h>

// Standard includes
#include <stdexcept>
#include <string>

class Settings {
public:
    /**
     * Constructor.  Requires non-null IVRSettings.
     */
    Settings(vr::IVRSettings* settings, const std::string& section = "driver_osvr");

    /**
     * Returns the setting value or returns @c value if the setting
     * doesn't exist.
     */
    template <typename T> T getSetting(const std::string& setting, const T& value);

private:
    /** \name Accessors for general values. */
    //@{
    template <typename T> T getSetting(identity<T>, const std::string& setting, const T& value);
    //@}

    /** \name Accessors and helper functions for boolean values. */
    //@{
    bool getSetting(identity<bool>, const std::string& setting, const bool& value);
    int32_t getSetting(identity<int32_t>, const std::string& setting, const int32_t& value);
    uint32_t getSetting(identity<uint32_t>, const std::string &setting, const uint32_t &value);
    float getSetting(identity<float>, const std::string& setting, const float& value);
    std::string getSetting(identity<std::string>, const std::string& setting, const std::string& value);
    //@}

    vr::IVRSettings* settings_ = nullptr;
    std::string section_;
};

inline Settings::Settings(vr::IVRSettings* settings, const std::string& section) : settings_(settings), section_(section)
{
    if (!settings) {
        throw std::invalid_argument("Must use non-null IVRSettings.");
    }
}

template<typename T> inline T Settings::getSetting(const std::string& setting, const T& value)
{
    // Redirect to the private method
    return getSetting(identity<T>(), setting, value);
}

template<typename T> inline T Settings::getSetting(identity<T>, const std::string& setting, const T& value)
{
    return getSetting<T>(identity<T>(), setting, value);
}

inline bool Settings::getSetting(identity<bool>, const std::string& setting, const bool& value)
{
    return settings_->GetBool(section_.c_str(), setting.c_str(), value);
}

inline float Settings::getSetting(identity<float>, const std::string& setting, const float& value)
{
    return settings_->GetFloat(section_.c_str(), setting.c_str(), value);
}

inline int32_t Settings::getSetting(identity<int32_t>, const std::string& setting, const int32_t& value)
{
    return settings_->GetInt32(section_.c_str(), setting.c_str(), value);
}

inline uint32_t Settings::getSetting(identity<uint32_t>, const std::string &setting, const uint32_t &uvalue)
{
    int32_t value;
    value = uvalue;

    return (uint32_t)settings_->GetInt32(section_.c_str(), setting.c_str(), value);
}

inline std::string Settings::getSetting(identity<std::string>, const std::string& setting, const std::string& value)
{
    char buf[1024];
    settings_->GetString(section_.c_str(), setting.c_str(), buf, sizeof(buf), value.c_str());
    std::string ret = buf;
    return ret;
}

#endif // INCLUDED_Settings_h_GUID_3C3922D1_0C13_4E57_9EE4_85E6F23FFC67

