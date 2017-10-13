#include "moon.h"

Moon::Moon() {}

Moon::Moon(string name) { oName = name; }
void Moon::addResourceDeposit(Resource oreDepo) { mOreDeposites.push_back(Resource(oreDepo.getID(), oreDepo.getName(),oreDepo.getDesc(),oreDepo.getType(),oreDepo.getStage(), oreDepo.getTier(), oreDepo.getBaseSz(), oreDepo.getSG2(),oreDepo.getOAmt())); }
void Moon::updateDeposite(int pos, string op, float newamt) { mOreDeposites.at(pos).updateOAmt(op, newamt); }
float Moon::getDepoAmt(int pos) { return mOreDeposites.at(pos).getOAmt(); }
string Moon::getDepoName(int pos) { return mOreDeposites.at(pos).getName(); }