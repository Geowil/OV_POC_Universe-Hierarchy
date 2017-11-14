#include "moon.h"
#include "util.h"
#include "dataSystem.h"
#include "settings.h"

namespace u = Util;
namespace setting = Settings;

dataSystem ds_mn;

Moon::Moon() {}

Moon::Moon(string name) { oName = name; }
void Moon::addResourceDeposit(Resource oreDepo) { mOreDeposites.push_back(Resource(oreDepo.getID(), oreDepo.getName(),oreDepo.getDesc(),oreDepo.getType(),oreDepo.getStage(), oreDepo.getTier(), oreDepo.getBaseSz(), oreDepo.getSG2(),oreDepo.getOAmt())); }
void Moon::updateDeposite(int pos, string op, float newamt) { mOreDeposites.at(pos).updateOAmt(op, newamt); }
float Moon::getDepoAmt(int pos) { return mOreDeposites.at(pos).getOAmt(); }
string Moon::getDepoName(int pos) { return mOreDeposites.at(pos).getName(); }

void Moon::setupMoon(float eks, float sec) {
	mnClsRand = u::getIRand(setting::mnClsRnd.iLow, setting::mnClsRnd.iHigh);

	for (setting::pltTypeSettings plt : setting::gPltTypSettings) {
		if (eks >= plt.getPltEksRng().fLow && eks <= plt.getPltEksRng().fHigh) {
			for (i1 = 0; i1 < plt.getPltMnClsSz() - 1; i1++) {
				if (i1 == 0 && (mnClsRand >= 1 && mnClsRand <= plt.getPltMnCls(i1))) {
					oCls = "Class " + to_string(i1);
				}
				else if (i1 != 0 && (mnClsRand >= plt.getPltMnCls(i1 - 1) && mnClsRand <= plt.getPltMnCls(i1))) {
					oCls = "Class " + to_string(i1);
				}
			}
		}
	}

	//Now setup deposits based on the class just obtained
	for (setting::moonClsSettings mcs : setting::gMnClsSettings) {
		//Determine size of deposite
		if (mcs.getMnCls() == oCls) {			
			numOfSmDepos = u::getIRand(mcs.getMnDpSmSpnRng.iLow, mcs.getMnDpSmSpnRng.iHigh);
			numOfMdDepos = u::getIRand(mcs.getMnDpMdSpnRng.iLow, mcs.getMnDpMdSpnRng.iHigh);
			numOfLgDepos = u::getIRand(mcs.getMnDpLgSpnRng.iLow, mcs.getMnDpLgSpnRng.iHigh);
			numOfHgDepos = u::getIRand(mcs.getMnDpHgSpnRng.iLow, mcs.getMnDpHgSpnRng.iHigh);

			//Go throuch each depo size class and create the depo
			if (numOfSmDepos > 0) {
				for (i1 = 0; i1 < numOfSmDepos; i1++) {
					oreTier = u::getFRand(setting::oreTrRnd.fLow, setting::oreTrRnd.fHigh);
					oreStage = u::getIRand(setting::oreStgRnd.iLow, setting::oreStgRnd.iHigh);
					baseDepoSz = u::getFRand(setting::dpoSmSz.fLow, setting::dpoSmSz.fHigh);

					procOreDepo1(sec, "Small");
				}
			}
			else if (numOfMdDepos > 0) {
				for (i1 = 0; i1 < numOfMdDepos; i1++) {
					oreTier = u::getFRand(setting::oreTrRnd.fLow, setting::oreTrRnd.fHigh);
					oreStage = u::getIRand(setting::oreStgRnd.iLow, setting::oreStgRnd.iHigh);
					baseDepoSz = u::getFRand(setting::dpoMdSz.fLow, setting::dpoMdSz.fHigh);

					procOreDepo1(sec, "Medium");
				}
			}
			else if (numOfLgDepos > 0) {
				for (i1 = 0; i1 < numOfLgDepos; i1++) {
					oreTier = u::getFRand(setting::oreTrRnd.fLow, setting::oreTrRnd.fHigh);
					oreStage = u::getIRand(setting::oreStgRnd.iLow, setting::oreStgRnd.iHigh);
					baseDepoSz = u::getFRand(setting::dpoLgSz.fLow, setting::dpoLgSz.fHigh);

					procOreDepo1(sec, "Large");
				}
			}
			else if (numOfHgDepos > 0) {
				for (i1 = 0; i1 < numOfHgDepos; i1++) {
					oreTier = u::getFRand(setting::oreTrRnd.fLow, setting::oreTrRnd.fHigh);
					oreStage = u::getIRand(setting::oreStgRnd.iLow, setting::oreStgRnd.iHigh);
					baseDepoSz = u::getFRand(setting::dpoHgSz.fLow, setting::dpoHgSz.fHigh);

					procOreDepo1(sec, "Huge");
				}
			}
		}
	}
}

void Moon::procOreDepo1(float sec, string dSz) {
	if (sec > setting::secRtHighRng.fLow) {
		//Figure out the tier of the ore to use
		for (setting::oreTierSettings tier : setting::gOreTierSettings) {
			if (oreTier >= tier.getHighRng().fLow && oreTier < tier.getHighRng().fHigh) {
				procOreDepo2(tier,dSz);
				break;
			}
		}
	}
	else if (sec > setting::secRtMidRng.fLow && sec <= setting::secRtMidRng.fHigh) {
		for (setting::oreTierSettings tier : setting::gOreTierSettings) {
			if (oreTier >= tier.getMidRng().fLow && oreTier < tier.getMidRng().fHigh) {
				procOreDepo2(tier, dSz);
				break;
			}
		}

	}
	else if (sec > setting::secRtLowRng.fLow && sec <= setting::secRtLowRng.fHigh) {
		for (setting::oreTierSettings tier : setting::gOreTierSettings) {
			if (oreTier >= tier.getLowRng().fLow && oreTier < tier.getLowRng().fHigh) {
				procOreDepo2(tier, dSz);
				break;
			}
		}

	}
	else if (sec <= setting::secRtNullRng.fLow) {
		for (setting::oreTierSettings tier : setting::gOreTierSettings) {
			if (oreTier >= tier.getNullRng().fLow && oreTier < tier.getNullRng().fHigh) {
				procOreDepo2(tier, dSz);
				break;
			}
		}
	}
}

void Moon::procOreDepo2(setting::oreTierSettings tier, string depoSz) {
	//Determine the size category of the asteroid
	if (depoSz == "Small") {
		//Determine the ore stage to use
		for (setting::roidStageSettings oreStg : setting::gRoidStgSettings) {
			if (oreStage >= oreStg.getRoidSmRng().iLow && oreStage <= oreStg.getRoidSmRng().iHigh) {
				procOreDepo3(tier, oreStg);
				break;
			}
		}
	}
	else if (depoSz == "Medium") {
		//Determine the ore stage to use
		for (setting::roidStageSettings oreStg : setting::gRoidStgSettings) {
			if (oreStage >= oreStg.getRoidMdRng().iLow && oreStage <= oreStg.getRoidMdRng().iHigh) {
				procOreDepo3(tier, oreStg);
				break;
			}
		}
	}
	else if (depoSz == "Large") {
		//Determine the ore stage to use
		for (setting::roidStageSettings oreStg : setting::gRoidStgSettings) {
			if (oreStage >= oreStg.getRoidLgRng().iLow && oreStage <= oreStg.getRoidLgRng().iHigh) {
				procOreDepo3(tier, oreStg);
				break;
			}
		}
	}
	else if (depoSz == "Huge") {
		//Determine the ore stage to use
		for (setting::roidStageSettings oreStg : setting::gRoidStgSettings) {
			if (oreStage >= oreStg.getRoidHgRng().iLow && oreStage <= oreStg.getRoidHgRng().iHigh) {
				procOreDepo3(tier, oreStg);
				break;
			}
		}
	}
}

void Moon::procOreDepo3(setting::oreTierSettings tier, setting::roidStageSettings oreStg) {
	getOre(to_string(tier.getTierVal()), to_string(oreStg.getStageI())); //Populate temp resource vector for further processing

																		 //Get a random val based on 0 to size of temp ore vect - 1
	if (tempResVec.size() > 0) {
		oreEle = u::getIRand(0, tempResVec.size() - 1);

		//Now use that ore in this asteroid
		baseOreSz = tempResVec.at(oreEle).getBaseSz();

		//asteroid size calcualtion
		tempOreSz = baseOreSz * u::getFRand(oreStg.getRoidOStgMulRnd().fLow, oreStg.getRoidOStgMulRnd().fHigh);
		tempOreSz = (((tempOreSz * 10) / 4) * oreStg.getRoidStgMulti());
		totalOreSz += tempOreSz;
	}
}

void Moon::getOre(string tier, string stage) {
	vector<string> conds = { "Type = 'Ore'", "Tier = " + tier , "Stage = " + stage };
	ds_mn.prepQuery("Resources", "select from where", 0, conds);

	strRescs = ds_mn.getRescs();

	for (strcResc rsc : strRescs) {
		tempResVec.push_back(Resource(rsc.id, rsc.name, rsc.desc, rsc.typ, rsc.stg, rsc.tier, rsc.bsize, rsc.sg2, 0.0f));
	}
}