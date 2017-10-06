#ifndef DATASTRUCTS__H
#define DATASTRUCTS__H

#include <string>
#include <vector>

using std::string;
using std::vector;

//Comments denote exact order of fields in database

//Database Structs
struct strcAPlating {
	string name, desc, cls; //1-3
	int id, tlvl, rdly; //0,4,11
	float pwrreq, cpureq, ramreq, drb, pwrcons, reprate, sg2; //5-10,12
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //13-20
};

struct strcCap {
	string name, desc; //1,2
	int id, tlvl; //0,3
	float cpureq, ramreq, capt, rchgrate, rchgamt, sg2; //4-9
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //10-17
};

struct strcClone {
	string name, desc, cls; //1-3
	int id, tlvl; //0,4
	float sg2; //5
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //6-13
};

//clone effect goes here

struct strcCpu {
	string name, desc, cls; //1-3
	int id, tlvl; //0,4
	float pwrreq, capt, sg2; //5-7
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //8-15
};

struct strcDisp {
	string disp; //1
	int id, relval; //0,2
};

//effects
//effect effect modifiers xref
//effect modifiers

struct strcEng {
	string name, desc, cls; //1-3
	int id, tlvl; //0,4
	float pwrreq, cpureq, ramreq, maxspd, acclrate, navadjrate, sg2; //5-11
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //12-19
};

struct strcEquipment {
	string name, desc, type, cls, subcls; //1-5
	int id,tlvl, targtime; //0,6,10
	float mindmg, maxdmg, maxdist, pwrreq, cpureq, ramreq, rchgrate, pwrcons, initpwrcon, dlytime, sg2; //7-9,11-18
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //19-26
};

//equipment effect xref

struct strcHull {
	string name, desc, cls; //1-3
	int id, tlvl, repdly; //0,4,11
	float pwrreq, cpureq, ramreq, reprate, pwrcons, repamt, drb, sg2; //5-10,12,13
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //14-21
};

struct strcMsg {
	string msg; //1
	int id; //0
};

struct strcMission {
	string name, desc, diff, sec, sys, targnm, targshpcls, type; //1-2,5-10
	int id,reqcel, tlim; //0,3,4
};

struct strcMReward {
	string rwdtyp; //1
	int id, rwdamt; //0,2
};

//mission mission rewards xref

struct strcName {
	string name, nmtyp, applraces; //1-3
};

struct strcNPCShp {
	string name, shpcls; //1-2
	int id, minlvrng, maxlvrng, basecxp; //0,3-5
};

struct strcODP {
	string name, desc, cls, subcls; //1-4
	int id, tlvl, cpu, ram, psys, cap, smtx, aplt, hull, wtsys, tslots, lslots, mslots, hslots,cxp; //0,5-17,28
	float sg2,cargo; //18-19
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //20-27
};

struct strcPShd {
	string name, desc; //1-2
	int id, tlvl, psys, cpu, ram, smtx, tslots, lslots, mslots; //0,3-10
	float sg2; //11
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //12-19
};

struct strcPSys {
	string name, desc, typ; //1-3
	int id, tlvl; //0,4
	float cpureq, ramreq, capt, sg2; //5-8
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //9-16
};

struct strcRace {
	string name,desc,emp,cap; //1-4
};

struct strcRam{
	string name, desc; //1-2
	int id, tlvl; //0,3
	float pwrreq, cpureq, capt, sg2; //4-7
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //8-15
};

struct strcRank {
	string name; //1
};

struct strcReproc {
	int id, oid, rid, rescost; //0-2,5
	float repunits, resprod, resprodloss; //3-4,6
};

//Requirement xref

struct strcResc {
	string name, desc, typ, ore; //1-2,4,8
	int id, stg, tier, xcost; //0,5,6,9
	float sg2, bsize; //3,7
};

struct strcSetting {
	string sKey; //1
	string sVal; //2
};

struct strcShpCls {
	string name; //1
	int id; //0
};

struct strcShip {
	string name,desc,cls,subcls; //1-4
	int id,tlvl, cpu, ram, psys, cap, eng, wfgen, smtx, aplt, hull, wtsys, tslots, lslots, mslots, hslots; //0,5-19
	float sg2, crg; //20-21
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //22-28
};

struct strcSkill {
	string name, desc, typ, sgrp; //1-4
	int id, ttm, xcost, cxpcost; //0,5,8-9
	float sg2; //6
};

struct strcSklTraining {
	int id, skid; //0-1
	float rk1TMod, rk2TMod, rk3TMod, rk4TMod, rk5TMod, rk6TMod, rk7TMod, rk8TMod, rk9TMod, rk10TMod; //2-11
};

struct strcSMtx {
	string name, desc; //1-2
	int id, tlvl; //0,3
	float pwrreq, cpureq, ramreq, rchgrate, pwrcons, rchgamt, rchgdly, capt, sg2; //4-12
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //13-20
};

struct strcSysName {
	string name; //1
	int id; //0
};

struct strcWeapon {
	string name,desc,cls,subcls; //1-4
	int id,tlvl, ammocap, ammocons; //0,5,9-10
	float pwrreq, cpureq, ramreq, mindmg, maxdmg, dmgintlow, dmginthi, mineffrng, maxeffrng, minopteffrng, maxopteffrng, atkspd, pwrcons, initpwrcon, mcdur, mcyld, mass, sg2; //6-8,11-25
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //26-33
};

//weapon ammo xref

struct strcWFGen {
	string name, desc; //1-2
	int id, tlvl; //0,3
	float pwrreq, cpureq, ramreq, pwrcons, wrpstblrate, maxspd, sg2; //4-10
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //11-18
};

struct strcWTSys {
	string name, desc; //1-2
	int id, tlvl, maxtrg, trgrate; //0,3-5
	float pwrreq, cpureq, ramreq, maxscnrng, sg2; //6-10
	int xcost, rcost, dcost, dicost, lcost, ucost, pcost, nwcost; //11-18
};


//Saveing and Loading Structs


//Misc Structs
struct invSetup {
	int iID;
	int iAmt;
	string iTyp;
};
#endif