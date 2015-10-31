#ifndef PORTAL_H
#define PORTAL_H

class Portal : public Entity
{
	public:
		void SetParameter(std::string p, std::string v);
		void OnCollision(Entity *e);
		
		Portal();
	private:
		std::string map;
		int toX, toY;
};

#endif