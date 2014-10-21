#ifndef SPEARMAN_H
#define SPEARMAN_H

class NPC : public EventEntity
{
	public:
		static BITMAP *_sprite;
		void SetParameter(std::string p, std::string v);
		void Interact();
		void Update();
		
		NPC();
		static Entity *Create();
	private:
		float speed;
		s
};

#endif