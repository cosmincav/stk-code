//  SuperTuxKart - a fun racing game with go-kart
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_CALLBACKS_HPP
#define HEADER_CALLBACKS_HPP

#include "graphics/irr_driver.hpp"

#include <irrlicht.h>

using namespace irr;

class callbase: public video::IShaderConstantSetCallBack
{
public:
    callbase()
    {
        firstdone = 0;
    }

protected:
    bool firstdone;

};

//

class NormalMapProvider: public callbase
{
public:
    virtual void OnSetConstants(video::IMaterialRendererServices *srv, int);

    NormalMapProvider(bool withLightmap)
    {
        m_with_lightmap = withLightmap;
    }

private:
    bool m_with_lightmap;
};

//

class WaterShaderProvider: public callbase
{
public:
    virtual void OnSetConstants(video::IMaterialRendererServices *srv, int);

    void enableFog(bool enable)
    {
        m_fog = enable;
    }

    void setSpeed(const float s1, const float s2)
    {
        m_water_shader_speed_1 = s1;
        m_water_shader_speed_2 = s2;
    }

    WaterShaderProvider()
    {
        m_dx_1 = 0.0f;
        m_dx_2 = 0.0f;
        m_dy_1 = 0.0f;
        m_dy_2 = 0.0f;

        m_fog = false;

        m_water_shader_speed_1 =
        m_water_shader_speed_2 = 0.0f;
    }

private:
    float m_dx_1, m_dy_1, m_dx_2, m_dy_2;
    float m_water_shader_speed_1;
    float m_water_shader_speed_2;
    bool m_fog;
};

//

class GrassShaderProvider: public callbase
{
public:
    virtual void OnSetConstants(video::IMaterialRendererServices *srv, int);

    GrassShaderProvider()
    {
        m_fog = false;
        m_angle =
        m_amplitude =
        m_speed = 0.0f;
    }

    void enableFog(bool enable)
    {
        m_fog = enable;
    }

    void update(const float dt);

private:
    bool m_fog;
    float m_angle, m_amplitude, m_speed;
};

//

class SplattingProvider: public callbase
{
public:
    virtual void OnSetConstants(video::IMaterialRendererServices *srv, int);

    SplattingProvider(bool lightmap)
    {
        m_light_dir_calculated = false;
        m_lightmap = lightmap;
    }

private:
    core::vector3df m_light_direction;
    bool m_light_dir_calculated;
    bool m_lightmap;
};

//

class SphereMapProvider: public callbase
{
public:
    virtual void OnSetConstants(video::IMaterialRendererServices *srv, int);

    SphereMapProvider()
    {
        m_light_direction = core::vector3df(-0.6f, -0.5f, -0.63f);
    }

private:
    core::vector3df m_light_direction;
};

//

class BubbleEffectProvider: public callbase
{
public:
    virtual void OnSetConstants(video::IMaterialRendererServices *srv, int);

    BubbleEffectProvider()
    {
        initial_time = irr_driver->getDevice()->getTimer()->getRealTime();
        m_transparency = 1.0f;
        m_visible = true;
    }

    void onMadeVisible()
    {
        m_visible = true;
    }

    void onHidden()
    {
        m_visible = false;
        m_transparency = 0.0f;
    }

    void isInitiallyHidden()
    {
        m_visible = false;
        m_transparency = 0.0f;
    }

private:
    u32 initial_time;
    float m_transparency;
    bool m_visible;
};

#endif