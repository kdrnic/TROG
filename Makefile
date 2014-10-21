norulespecified: all

Enemies: obj/Enemy.o HitHurtEnemies obj/Skeleton.o obj/Archer.o obj/Werewolf.o

Engine: obj/EntitiesManager.o obj/Entity.o obj/Game.o obj/InventoryManager.o obj/Keys.o obj/Map.o obj/MapManager.o obj/Utils.o

Entities: obj/SpriteEntity.o obj/Player.o Enemies OtherEntities EventEntities ItemPickups

EventEntities: obj/EventEntity.o obj/Sign.o obj/Door.o obj/NPC.o

HitHurtEnemies: obj/HitHurtEnemy.o obj/Zombie.o obj/BarbedWire.o obj/Bat.o obj/Rat.o obj/Slime.o

ItemPickups: obj/ItemPickup.o obj/BombPickup.o

Items: obj/AK47.o obj/AKMagazine.o Swords LimitedAmountItems

LimitedAmountItems: obj/LimitedAmountItem.o obj/BombItem.o

OtherEntities: obj/AKBullet.o obj/Bomb.o obj/Explosion.o obj/Rock.o obj/Heart.o obj/Poof.o obj/Portal.o obj/Vampire.o obj/Stake.o obj/Trap.o obj/Plague.o obj/Goo.o obj/Arrow.o

Swords: obj/GenericSword.o obj/Sword.o

TROG: obj/main.o Engine Items Entities
	g++ -g -Wreturn-type -Werror obj/main.o obj/EntitiesManager.o obj/Entity.o obj/Game.o obj/InventoryManager.o obj/Keys.o obj/Map.o obj/MapManager.o obj/Utils.o obj/AK47.o obj/AKMagazine.o obj/GenericSword.o obj/Sword.o obj/LimitedAmountItem.o obj/BombItem.o obj/SpriteEntity.o obj/Player.o obj/Enemy.o obj/HitHurtEnemy.o obj/Zombie.o obj/BarbedWire.o obj/Bat.o obj/Rat.o obj/Slime.o obj/Skeleton.o obj/Archer.o obj/Werewolf.o obj/AKBullet.o obj/Bomb.o obj/Explosion.o obj/Rock.o obj/Heart.o obj/Poof.o obj/Portal.o obj/Vampire.o obj/Stake.o obj/Trap.o obj/Plague.o obj/Goo.o obj/Arrow.o obj/EventEntity.o obj/Sign.o obj/Door.o obj/NPC.o obj/ItemPickup.o obj/BombPickup.o -o TROG -lalleg

all: TROG

obj/main.o: main.cpp
	g++ -g -Wreturn-type -Werror -c main.cpp -o obj/main.o -lalleg

obj/EntitiesManager.o: EntitiesManager.cpp EntitiesManager.h
	g++ -g -Wreturn-type -Werror -c EntitiesManager.cpp -o obj/EntitiesManager.o -lalleg

obj/Entity.o: Entity.cpp Entity.h
	g++ -g -Wreturn-type -Werror -c Entity.cpp -o obj/Entity.o -lalleg

obj/Game.o: Game.cpp Game.h
	g++ -g -Wreturn-type -Werror -c Game.cpp -o obj/Game.o -lalleg

obj/InventoryManager.o: InventoryManager.cpp InventoryManager.h
	g++ -g -Wreturn-type -Werror -c InventoryManager.cpp -o obj/InventoryManager.o -lalleg

obj/Keys.o: Keys.cpp Keys.h
	g++ -g -Wreturn-type -Werror -c Keys.cpp -o obj/Keys.o -lalleg

obj/Map.o: Map.cpp Map.h
	g++ -g -Wreturn-type -Werror -c Map.cpp -o obj/Map.o -lalleg

obj/MapManager.o: MapManager.cpp MapManager.h
	g++ -g -Wreturn-type -Werror -c MapManager.cpp -o obj/MapManager.o -lalleg

obj/Utils.o: Utils.cpp Utils.h
	g++ -g -Wreturn-type -Werror -c Utils.cpp -o obj/Utils.o -lalleg

obj/AK47.o: AK47.cpp AK47.h
	g++ -g -Wreturn-type -Werror -c AK47.cpp -o obj/AK47.o -lalleg

obj/AKMagazine.o: AKMagazine.cpp AKMagazine.h
	g++ -g -Wreturn-type -Werror -c AKMagazine.cpp -o obj/AKMagazine.o -lalleg

obj/GenericSword.o: GenericSword.cpp GenericSword.h
	g++ -g -Wreturn-type -Werror -c GenericSword.cpp -o obj/GenericSword.o -lalleg

obj/Sword.o: Sword.cpp Sword.h
	g++ -g -Wreturn-type -Werror -c Sword.cpp -o obj/Sword.o -lalleg

obj/LimitedAmountItem.o: LimitedAmountItem.cpp LimitedAmountItem.h
	g++ -g -Wreturn-type -Werror -c LimitedAmountItem.cpp -o obj/LimitedAmountItem.o -lalleg

obj/BombItem.o: BombItem.cpp BombItem.h
	g++ -g -Wreturn-type -Werror -c BombItem.cpp -o obj/BombItem.o -lalleg

obj/SpriteEntity.o: SpriteEntity.cpp SpriteEntity.h
	g++ -g -Wreturn-type -Werror -c SpriteEntity.cpp -o obj/SpriteEntity.o -lalleg

obj/Player.o: Player.cpp Player.h
	g++ -g -Wreturn-type -Werror -c Player.cpp -o obj/Player.o -lalleg

obj/Enemy.o: Enemy.cpp Enemy.h
	g++ -g -Wreturn-type -Werror -c Enemy.cpp -o obj/Enemy.o -lalleg

obj/HitHurtEnemy.o: HitHurtEnemy.cpp HitHurtEnemy.h
	g++ -g -Wreturn-type -Werror -c HitHurtEnemy.cpp -o obj/HitHurtEnemy.o -lalleg

obj/Zombie.o: Zombie.cpp Zombie.h
	g++ -g -Wreturn-type -Werror -c Zombie.cpp -o obj/Zombie.o -lalleg

obj/BarbedWire.o: BarbedWire.cpp BarbedWire.h
	g++ -g -Wreturn-type -Werror -c BarbedWire.cpp -o obj/BarbedWire.o -lalleg

obj/Bat.o: Bat.cpp Bat.h
	g++ -g -Wreturn-type -Werror -c Bat.cpp -o obj/Bat.o -lalleg

obj/Rat.o: Rat.cpp Rat.h
	g++ -g -Wreturn-type -Werror -c Rat.cpp -o obj/Rat.o -lalleg

obj/Slime.o: Slime.cpp Slime.h
	g++ -g -Wreturn-type -Werror -c Slime.cpp -o obj/Slime.o -lalleg

obj/Skeleton.o: Skeleton.cpp Skeleton.h
	g++ -g -Wreturn-type -Werror -c Skeleton.cpp -o obj/Skeleton.o -lalleg

obj/Archer.o: Archer.cpp Archer.h
	g++ -g -Wreturn-type -Werror -c Archer.cpp -o obj/Archer.o -lalleg

obj/Werewolf.o: Werewolf.cpp Werewolf.h
	g++ -g -Wreturn-type -Werror -c Werewolf.cpp -o obj/Werewolf.o -lalleg

obj/AKBullet.o: AKBullet.cpp AKBullet.h
	g++ -g -Wreturn-type -Werror -c AKBullet.cpp -o obj/AKBullet.o -lalleg

obj/Bomb.o: Bomb.cpp Bomb.h
	g++ -g -Wreturn-type -Werror -c Bomb.cpp -o obj/Bomb.o -lalleg

obj/Explosion.o: Explosion.cpp Explosion.h
	g++ -g -Wreturn-type -Werror -c Explosion.cpp -o obj/Explosion.o -lalleg

obj/Rock.o: Rock.cpp Rock.h
	g++ -g -Wreturn-type -Werror -c Rock.cpp -o obj/Rock.o -lalleg

obj/Heart.o: Heart.cpp Heart.h
	g++ -g -Wreturn-type -Werror -c Heart.cpp -o obj/Heart.o -lalleg

obj/Poof.o: Poof.cpp Poof.h
	g++ -g -Wreturn-type -Werror -c Poof.cpp -o obj/Poof.o -lalleg

obj/Portal.o: Portal.cpp Portal.h
	g++ -g -Wreturn-type -Werror -c Portal.cpp -o obj/Portal.o -lalleg

obj/Vampire.o: Vampire.cpp Vampire.h
	g++ -g -Wreturn-type -Werror -c Vampire.cpp -o obj/Vampire.o -lalleg

obj/Stake.o: Stake.cpp Stake.h
	g++ -g -Wreturn-type -Werror -c Stake.cpp -o obj/Stake.o -lalleg

obj/Trap.o: Trap.cpp Trap.h
	g++ -g -Wreturn-type -Werror -c Trap.cpp -o obj/Trap.o -lalleg

obj/Plague.o: Plague.cpp Plague.h
	g++ -g -Wreturn-type -Werror -c Plague.cpp -o obj/Plague.o -lalleg

obj/Goo.o: Goo.cpp Goo.h
	g++ -g -Wreturn-type -Werror -c Goo.cpp -o obj/Goo.o -lalleg

obj/Arrow.o: Arrow.cpp Arrow.h
	g++ -g -Wreturn-type -Werror -c Arrow.cpp -o obj/Arrow.o -lalleg

obj/EventEntity.o: EventEntity.cpp EventEntity.h
	g++ -g -Wreturn-type -Werror -c EventEntity.cpp -o obj/EventEntity.o -lalleg

obj/Sign.o: Sign.cpp Sign.h
	g++ -g -Wreturn-type -Werror -c Sign.cpp -o obj/Sign.o -lalleg

obj/Door.o: Door.cpp Door.h
	g++ -g -Wreturn-type -Werror -c Door.cpp -o obj/Door.o -lalleg

obj/NPC.o: NPC.cpp NPC.h
	g++ -g -Wreturn-type -Werror -c NPC.cpp -o obj/NPC.o -lalleg

obj/ItemPickup.o: ItemPickup.cpp ItemPickup.h
	g++ -g -Wreturn-type -Werror -c ItemPickup.cpp -o obj/ItemPickup.o -lalleg

obj/BombPickup.o: BombPickup.cpp BombPickup.h
	g++ -g -Wreturn-type -Werror -c BombPickup.cpp -o obj/BombPickup.o -lalleg

