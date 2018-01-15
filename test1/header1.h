#pragma once

#define MAX 150
#define monMax 500
#define initATK 20
#define monATK 40;



//�^�[�����̏�����
int TURN = 1;

/*-------------------------
�A�C�e���̍\���̂̐錾
flag = �������Ă�����true,
�@ �����ɂ����false
  name = �A�C�e���̖��O
  description = �A�C�e���̐���
  --------------------------*/
struct Item {
	bool flag;
	char* name;
	char* description;
};

/*----------------------
�A�C�e���̍\���̂̏�����
item[0] = ���C�g
item[1] = �c���
item[2] = ���L�P
item[3] = ���L�Q
item[4] = �{
-----------------------*/
//�A�C�e���̐�������ύX���A�{��ǂ�ł������ɂ̓��C�g�̌��ʂ��ڂ����\������悤�ɕύX
struct Item item[]{
	//���C�g�̌���:�����X�^�[����̃_���[�W��120��40(1/3��)
	{ false, "���C�g", "�Â��ꏊ�ł��悭������!\n�������͌��Ɏア���߁A�Ђ�܂��邱�Ƃ��ł���B\n�퓬�̍ہA�펞����������̃_���[�W�ʂ����炷���Ƃ��ł���B" },
	{ false, "�c����̏�","�}���قŌ������{��ǂނ��Ƃ��ł���B\n�u������߂�v��I���������A�̗͂�10�񕜂��邱�Ƃ��ł���B" },
	{ false, "���L�P","�ǂ���炱�̓��L�͉��~�̎�l�̕��̂悤��\n\n�����w��\n���̍Ȃ�����ł��܂��Ă���ǂ�قǌo�������낤��\n�Ȃ����Ȃ��Ȃ������̓�����O�ɏo���L�����Ȃ�\n���̂܂܂��̐����������̂��낤��\n\n��������\n�}�����ł������Ȗ{��������\n�ǂ���玀�҂𐶂��Ԃ点����@��������Ă���悤��\n���͂���ɑS�Ă������Ă݂悤�Ǝv��\n\n���L�͂����ŏI����Ă���悤��..." },
	{ false, "���L�Q","�����w��\n���ɖ����Ȃ�h�点�鏀����������\n���@�w��`���A�O�̂��߂ɕ�����p�ӂ���\n���ׂĂ͖������܂�\n\n��������\n�Ȃ�h�点�邱�Ƃɐ�������!\n�Ȃ͂��̓����Y��Ȏp�̂܂܂�\n����ł��̓��̂悤�ɍK���ɕ�点��\n\n��������\n����͎��̍Ȃł͂Ȃ�\n���͂����������𐶂ݏo���������������̂�\n�������̉��~���瓦���悤�Ǝv��\n�������̓��L��ǂ�ł���l������̂Ȃ�\n�����ɓ����邱�Ƃ��������߂���\n\n���L�͂����ŏI����Ă���悤��..." },
	{ false, "�{","�c����̏����{��ǂ݁A���e�������Ă��ꂽ�B\n�{�ɂ͐l�𐶂��Ԃ点����@�������Ă���悤���B\n���@�͒P���ŁA���@�w�̏�Ɏ��̂��悹�邾���炵���B\n�������A�h�����l�͋�ƌ��Ɏキ�Ȃ��Ă��܂��悤���B\n" },
};

/*-------------------------
����̍\���̂̐錾
flag = �������Ă�����true,
�����ɂ���Ȃ�false
name = ����̖��O
status = ����̍U����
dice = �U���̐�������̊
explain = ����
--------------------------*/
struct Weapon {
	bool flag;
	char* name;
	int status;
	int dice;
	char* explain;
};

/*----------------------
����̍\���̂̏�����
weapon[0] = �f��
weapon[1] = ��p�C�v
weapon[2] = �n���}�[
weapon[3] = ��
-----------------------*/
struct Weapon weapon[]{
	{ true, "�f��", 0, 1,"�f��" },
	{ false, "��p�C�v",20,1,"��łł��Ă���p�C�v�̂悤���B" },
	{ false, "�n���}�[",40,2 ,"�����󂷂Ƃ��ɖ𗧂��������B" },
	{ false, "��",20,1 ,"�ƂĂ��������Ȍ����B" },
};

/*---------------------------------------------
�����̍\���̂̐錾
item1 = �����ɂ���A�C�e���̃A�h���X�i�|�C���^�j
item2 = �V
weapon = �����ɂ��镐��̃A�h���X�i�|�C���^�j
locked = �����������Ă���Ȃ�true,
�����������Ă��Ȃ��Ȃ�false
name = ������
next = �s����̕����̃A�h���X�i�|�C���^�j
floor = �K��
------------------------------------------------*/
struct Room {
	struct Item *item1;
	struct Item *item2;
	struct Weapon *weapon;
	bool locked;
	char* name;
	struct Room *next, *next2, *next3, *next4, *next5;
	int floor;
};

/*-------------------
�����̍\���̂̏�����
room[0] = �n����
room[1] = �P�K
room[2] = �Q�K
room[3] = �}����
room[4] = �����P
room[5] = �����Q
room[6] = �����R
room[7] = ����
---------------------*/
struct Room room[] = {
	{ NULL, NULL, NULL, false, "�n����", NULL, NULL , NULL , NULL , NULL, 0 },
	{ NULL, NULL, NULL, false, "�P�K�@", NULL, NULL , NULL , NULL , NULL, 1 },
	{ NULL, NULL, NULL, false, "�Q�K�@", NULL, NULL , NULL , NULL , NULL, 2 },
	{ NULL, NULL, NULL, false, "�}����", NULL, NULL , NULL , NULL , NULL, 1 },
	{ NULL, NULL, NULL, false, "���u�@", NULL, NULL , NULL , NULL , NULL, 1 },
	{ NULL, NULL, NULL, false, "�Q���@", NULL, NULL , NULL , NULL , NULL, 2 },
	{ NULL, NULL, NULL, false, "��Ɂ@", NULL, NULL , NULL , NULL , NULL,2 },
	{ NULL, NULL, NULL, false, "���ց@", NULL, NULL , NULL , NULL , NULL, 0 }
};

/*----------------------------------------------------------
��l���̍\���̂̐錾
HP = ��l����HP
ATK = ��l���̍U����
LightFlag = ���C�g�������Ă�����true,
�����Ă��Ȃ�������false
LadyFlag = �c����̏������p�[�e�B�[�ɂ����true,
���Ȃ�������false
DefeatFlag = ��������|������true,
�|���ĂȂ�������false
Location = ��l���̌��ݒn�̃A�h���X�i�|�C���^�j
weapon = ��l���̑������Ă��镐��̃A�h���X�i�|�C���^�j
-----------------------------------------------------------*/
struct player {
	int HP;
	int ATK;
	bool LightFlag;
	bool LadyFlag;
	bool DefeatMonster;
	struct Room *Location;
	struct Weapon *weapon;
};

/*-----------------------------------------------
�������̍\���̂̐錾
HP = ��������HP
ATK = �������̍U����
Location = �������̌��ݒn�̃A�h���X�i�|�C���^�j
-------------------------------------------------*/
struct monster {
	int HP;
	int ATK;
	struct Room *Location;
	bool defeated;
};

void explain();
void initRandom();
void initRoom();
struct player initPlayer();
struct monster initMonster();
void showMap(struct player *player, struct monster *monster);
int Random(int x);
char enterSomething();
void monsterCrow(struct player *player, struct monster *monster);
void ifLose(struct player *player, struct monster *monster);
bool Battle(struct player *player, struct monster *monster);
void hide(struct player *player, struct monster *monster);
void changeWeapon(struct player *player);
void doNothing(struct player *player);
void printChoiceItem(int num, char c, struct Room *newRoom, struct Item *newItem);
void printChoiceWeapon(struct Room *newRoom, struct Weapon *newWeapon);
void printChoiceDoor(struct Room *newRoom, struct Room *door);
void moveRoom(struct player *player, struct Room *newRoom, struct monster *monster);
void getItem(struct Item *newItem);
void destruction(struct player *player, struct Room *newRoom, struct monster *monster);
void selectRoom(struct player *player, struct Room *newRoom, struct monster *monster);
void selectItem(struct Item *newItem);
void setWeapon(struct player *player, struct Weapon *newWeapon);
void selectWeapon(struct Weapon *newWeapon, struct player *player);
void Move(struct player *player, struct monster *monster);
void moveMonster(struct player *player, struct monster *monster);
void countTurn(struct player *player, struct monster *monster);
void enter();
void Tutorial(struct  player *player);