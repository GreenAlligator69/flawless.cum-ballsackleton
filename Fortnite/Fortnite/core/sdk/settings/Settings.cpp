#pragma once
#include "../../inc.hpp"

auto settings::c_vars::load( ) -> void
{
	this->aim.enabled       = true;
	this->aim.target_bone   = 109;
	this->aim.fov_c			= 150.f;
	this->aim.aim_keycode   = 0x02;
	this->aim.smooth		= 3.4f;
	this->aim.accuracy_rate = 10.0f;

	this->aim.prediction = true;

	this->aim.ignore_invisible = true;
	this->aim.ignore_knocked = true;
	this->aim.ignore_team = true;

	this->weapon_config.smg.enabled = true;
	this->weapon_config.smg.weapon_fov = this->aim.fov_c;
	this->weapon_config.smg.prediction = true;

	this->weapon_config.ars.enabled = true;
	this->weapon_config.ars.weapon_fov = this->aim.fov_c;
	this->weapon_config.ars.prediction = true;

	this->weapon_config.shotgun.enabled = true;
	this->weapon_config.shotgun.weapon_fov = this->aim.fov_c;

	this->weapon_config.pistol.enabled = true;
	this->weapon_config.pistol.weapon_fov = this->aim.fov_c;
	this->weapon_config.pistol.prediction = true;

	this->weapon_config.snipers.enabled = true;
	this->weapon_config.snipers.weapon_fov = this->aim.fov_c;
	this->weapon_config.snipers.prediction = true;

	this->visuals.esp		= true;
	this->visuals.bounding_box		= false;
	this->visuals.bounding_corner	= true;
	this->visuals.bounding_3d		= false;
	this->visuals.skeleton  = true;
	this->visuals.corner    = false;
	this->visuals.distance	= true;
	this->visuals.snapline	= true;
	this->visuals.username  = true;
	this->visuals.weapon    = true;
	this->visuals.ignore_team = false;
	this->visuals.ignore_knocked = true;

	this->radar.enabled     = true;
	this->radar.height      = 200;
	this->radar.width       = 200;
	this->radar.show_team   = true;


	this->misc.fov			= true;
	this->misc.fps			= true;
	this->misc.menu			= false;
	this->misc.trigger_bot  = false;
	this->misc.crosshair	= true;

	this->misc.kill         = false;

	this->misc.custom_delay = 50;
	this->misc.maximum_distance = 200.f;
	this->misc.has_clicked;
	this->misc.tb_begin;
	this->misc.tb_end;
	this->misc.tb_time_since;

}

auto settings::c_vars::save( ) -> void
{

}

auto settings::c_vars::reset( ) -> void
{

}