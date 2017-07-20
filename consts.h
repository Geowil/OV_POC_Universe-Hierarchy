#pragma once
#ifndef CONSTS_H
#define CONSTS_H

#include <string>
#include <utility>

static std::string sysNames[5] = { "System A","System B","System C","System D","System E" };
static std::string oreNames[9] = { "Ore 1A","Ore 2A","Ore 3A","Ore 1B","Ore 2B","Ore 3B","Ore 1C","Ore 2C","Ore 3C" };
static int oreBVal[9] = { 11000,9340,14000,6500,4360,7630,2550,2490,2000 };
static float oreSG2[9] = { 0.12f,0.15f,0.18f,0.22f,0.28f,0.26f,0.40f,0.46f,0.43f };
static float astSMulti[3] = { 1.12f,1.03f,0.98f };
static std::string plDefNames[8] = { "Defense A","Defense B","Defense C","Defense D","Defense E","Defense F","Defense G","Defense H" };
static std::string plShdNames[8] = { "Shield A","Shield B","Shield C","Shield D","Shield E","Shield F","Shield G","Shield H" };
static std::pair<float, float> roidOSSMulti[3] = { std::make_pair(0.3f,1.68f),std::make_pair(0.2f,1.52f),std::make_pair(0.1f,1.18f) };
static std::string rNumerals[10] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X" };
#endif