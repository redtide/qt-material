#pragma once

// https://github.com/material-foundation/material-tokens/blob/main/dsp/dist/styledictionary/android/colors.xml
// https://github.com/material-foundation/material-tokens/blob/main/dsp/dist/styledictionary/scss/variables.scss

#include "palette-reference.hpp"

namespace material {
namespace palette_system {
namespace light {
    static constexpr rgba primary               { palette_reference::primary40 };
    static constexpr rgba on_primary            { palette_reference::primary100 };
    static constexpr rgba primary_container     { palette_reference::primary90 };
    static constexpr rgba on_primary_container  { palette_reference::primary10 };
    static constexpr rgba secondary             { palette_reference::secondary40 };
    static constexpr rgba on_secondary          { palette_reference::secondary100 };
    static constexpr rgba secondary_container   { palette_reference::secondary90 };
    static constexpr rgba on_secondary_container{ palette_reference::secondary10 };
    static constexpr rgba tertiary              { palette_reference::tertiary40 };
    static constexpr rgba on_tertiary           { palette_reference::tertiary100 };
    static constexpr rgba tertiary_container    { palette_reference::tertiary90 };
    static constexpr rgba on_tertiary_container { palette_reference::tertiary10 };
    static constexpr rgba error                 { palette_reference::error40 };
    static constexpr rgba on_error              { palette_reference::error100 };
    static constexpr rgba error_container       { palette_reference::error90 };
    static constexpr rgba on_error_container    { palette_reference::error10 };
    static constexpr rgba background            { palette_reference::neutral99 };
    static constexpr rgba on_background         { palette_reference::neutral10 };
    static constexpr rgba surface               { background };
    static constexpr rgba on_surface            { on_background };
    static constexpr rgba surface_variant       { palette_reference::neutral90 };
    static constexpr rgba on_surface_variant    { palette_reference::neutral30 };
    static constexpr rgba inverse_surface       { palette_reference::neutral20 };
    static constexpr rgba inverse_on_surface    { palette_reference::neutral95 };
    static constexpr rgba outline               { palette_reference::neutral_variant50 };
    static constexpr rgba shadow                { palette_reference::neutral0 };
    static constexpr rgba inversePrimary        { palette_reference::primary80 };
} // namespace light

namespace dark {
    static constexpr rgba primary               { palette_reference::primary80 };
    static constexpr rgba on_primary            { palette_reference::primary20 };
    static constexpr rgba primary_container     { palette_reference::primary30 };
    static constexpr rgba on_primary_container  { palette_reference::primary90 };
    static constexpr rgba secondary             { palette_reference::secondary80 };
    static constexpr rgba on_secondary          { palette_reference::secondary20 };
    static constexpr rgba secondary_container   { palette_reference::secondary30 };
    static constexpr rgba on_secondary_container{ palette_reference::secondary90 };
    static constexpr rgba tertiary              { palette_reference::tertiary80 };
    static constexpr rgba on_tertiary           { palette_reference::tertiary20 };
    static constexpr rgba tertiary_container    { palette_reference::tertiary30 };
    static constexpr rgba on_tertiary_container { palette_reference::tertiary90 };
    static constexpr rgba error                 { palette_reference::error80 };
    static constexpr rgba on_error              { palette_reference::error20 };
    static constexpr rgba error_container       { palette_reference::error30 };
    static constexpr rgba on_error_container    { palette_reference::error90 };
    static constexpr rgba background            { palette_reference::neutral10 };
    static constexpr rgba on_background         { palette_reference::neutral90 };
    static constexpr rgba surface               { background };
    static constexpr rgba on_surface            { on_background };
    static constexpr rgba surface_variant       { palette_reference::neutral30 };
    static constexpr rgba on_surface_variant    { palette_reference::neutral80 };
    static constexpr rgba inverse_surface       { palette_reference::neutral90 };
    static constexpr rgba inverse_on_surface    { palette_reference::neutral20 };
    static constexpr rgba outline               { palette_reference::neutral60 };
    static constexpr rgba shadow                { palette_reference::neutral0 };
    static constexpr rgba inversePrimary        { palette_reference::primary40 };
} // namespace light

} // namespace palette_system
} // namespace material
