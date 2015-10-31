#ifndef VILLAGEWALL_H
#define VILLAGEWALL_H

class VillageWall : public Entity
{
	public:
		void SetParameter(std::string p, std::string v);
		void OnCollision(Entity *e);
		
		VillageWall();
	private:
		int coolDown;
};

#endif