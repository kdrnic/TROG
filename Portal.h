#ifndef PORTAL_H
#define PORTAL_H

class Portal : public Entity
{
	public:
		void SetParameter(std::string p, std::string v);
		void OnCollision(Entity *e);
		
		Portal();
		static Entity *Create();
	private:
		std::string map;
		int toX, toY;
};

#endif