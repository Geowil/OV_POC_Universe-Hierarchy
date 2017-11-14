#ifndef MOON_H
#define MOON_H

#include <string>
#include <vector>
#include "object.h"
#include "resource.h"
#include "settings.h"
#include "dataStructs.h"

using std::string;
using std::vector;

namespace setting = Settings;

class Moon : public Object{
public:
	Moon();
	Moon(string name);

	void setupMoon(float eks, float sec);
	void getOre(string tier, string stage);
	void procOreDepo1(float sec, string dSz);
	void procOreDepo2(setting::oreTierSettings tier, string depoSz);
	void procOreDepo3(setting::oreTierSettings tier, setting::roidStageSettings oreStg);

	void addResourceDeposit(Resource oreDeop);
	void updateDeposite(int pos, string op, float newamt);

	float getDepoAmt(int pos);
	string getDepoName(int pos);

private:
	vector<Resource> mOreDeposites;
	int mnClsRand, numOfSmDepos, numOfMdDepos, numOfLgDepos, numOfHgDepos, oreStage;
	int i1, oreEle;

	float baseDepoSz,baseOreSz,tempDepoSz,tempOreSz,totalDepoSz,totalOreSz, oreTier;
	vector<Resource> tempResVec; //Temp vector storage for processing
	vector<strcResc> strRescs; //Vector to store the struct representation data

};
#endif

/*
Moon Sizes:

Moon sizes will differ from planets.  There will be no EKS values and there will be more of a range.

In general, no moon should exceed half the size of its parent.  So will need to consider how to codify the planet size range in related to moons.  Obviously, the largest of the moons will be used along side class 5 planets (class = eks in this context).

Questions to think about:
Will there be an equal number of sizes across all planet classes? No.


What are the sizes (classes) and how should they be distributed?
1-15

Class 0 Planet: Class 1 Moons only
Class 1 Planet: 1-4 Class Moons
Class 2 Planet: 1-7 Class Moons
Class 3 Planet: 1-8 Class Moons
Class 4 Planet: 1-11 Class Moons
Class 5 Planet: any moon

Side note: In UR4 will have to actually define a relative size in some form of diameter value so that planets and moons can be generated in 3D space



What should be the ratio and volume of ore deposites on moons based on the size, and if so what would that be? Yes.
	Obviously, smaller moons should have fewer to no large deposites and moderate to few smaller ones.  Larger planets should have a balanced approach with a good number of large and a larger number of small deposites.  Teir 1 to 2 Only!  This would also then have to be based
	on security rating for the types of ores available (oh joy....).

	Deposite sizes: small, medium, large, huge

	Amount per deposite type would vary based on the types of ores using some kind of similar methodology as asteroid belts where you have a base depo size and then fill it based on sg2 of ore.

	Class 1 Moons: at most 4 small depos, 1 med depo, no others.
	Class 2 - 6 Moons: at most 13 small deposites, 2 med, 2 large, no others.
	Class 7-12 Moons: at most 30 small deposites, 14 med, 10 large, 2 huge.
	Class 13+ Moons: at most 50 small deposites, 25 med, 18 large, 8 huge.

	More deposite sizes could be added in the future.

	All of this needs to be encapsulated within settings (oh joy again....) along with the ranges for the conditionals to generate the depos in this fashion (a lot of ****ing settings).


At what size should moons be considered potentially habitable either naturally or through terraforming?
	Anything under class 4 is basically a dead moon that is much too small to maintain an atmosphere even with gravimetrics.  These would be only just larger than some of the largest asteroids.

	Class 5-12 moons should be terraformable but only sustain small colonies with require a large supply source for resources.
	Class 13+ moons should be terraformable but only sustain a moderate sized colony (no more than 30,000 population) and will require less resources than other types of habitable moons.  These classes can also be generated as habitable without terraforming.


If a moon can be made habitable, what kinds of factors and systems used with planet colinization should/can apply?
	If habitable via terraforming only a few should be used:
		Surface radiation
		Surface pollution
		Pop. Equqalibrium (very important for these types of colonies)

		Some types of resources needed to sustain a colony should be present but others should not be (maybe no liquid water) which will build the basis for what resources must be regularly delivered to the colony for it to survive.
		No colonization system like for planets, just send colonists with some starting resources to build and sustain and allow some control over colony progression through some of the edict system.  Colony will ultimatly survive or fail based
		on timely delivery of resrouces required per colony needs.

	If the moon was already habitable then all should be used but similar to above no formal colonization process.  In this case though the colony will just grow to the population size indicated by the player, player will have access to some of the edict system.

	Moons cannot progress past "colonization era", will always remain a singular colony but mining a colonized moon will result in faster resource generation.

	Mooner colonies will required protetion as well as they will not be able to support shields or defenses themselves; will not be a part of planetary invasion and planetary defenses will not extend to moons or stations.  Player will either have to allocate/require allocation of military resources
	from planet defense to defend each moon or hire mercenaries.


Should there be an algorithm to determine how many moons can be created per planet based on the size of the moons (similar to asteroids in belts)? Probably.  What these would look like, don't know right now.  Obviously, larger classes of planets get more moons though this
should not be a strict rule, should employ a similar outliers system to what is present for planet creation.  There will be more than two possibilities though (perc chance for up to certain numbers of moons per normal and per outlier [settings hell!!!]).



*/