#pragma once

#define MAX 150
#define monMax 500
#define initATK 20
#define monATK 40;



//ターン数の初期化
int TURN = 1;

/*-------------------------
アイテムの構造体の宣言
flag = 所持していたらtrue,
　 部屋にあればfalse
  name = アイテムの名前
  description = アイテムの説明
  --------------------------*/
struct Item {
	bool flag;
	char* name;
	char* description;
};

/*----------------------
アイテムの構造体の初期化
item[0] = ライト
item[1] = 幼馴染
item[2] = 日記１
item[3] = 日記２
item[4] = 本
-----------------------*/
//アイテムの説明文を変更し、本を読んでいた時にはライトの効果を詳しく表示するように変更
struct Item item[]{
	//ライトの効果:モンスターからのダメージ量120→40(1/3に)
	{ false, "ライト", "暗い場所でもよく見える!\n化け物は光に弱いため、ひるませることができる。\n戦闘の際、常時化け物からのダメージ量を減らすことができる。" },
	{ false, "幼馴染の女","図書館で見つけた本を読むことができる。\n「息を潜める」を選択した時、体力を10回復することができる。" },
	{ false, "日記１","どうやらこの日記は屋敷の主人の物のようだ\n\n○月Ｘ日\n私の妻が死んでしまってからどれほど経っただろうか\n妻がいなくなったあの日から外に出た記憶がない\nこのままこの生活が続くのだろうか\n\n○月△日\n図書室でおかしな本を見つけた\nどうやら死者を生き返らせる方法が書かれているようだ\n私はこれに全てを懸けてみようと思う\n\n日記はここで終わっているようだ..." },
	{ false, "日記２","□月Ｘ日\nついに明日妻を蘇らせる準備が整った\n魔法陣を描き、念のために武器も用意した\nすべては明日決まる\n\n□月△日\n妻を蘇らせることに成功した!\n妻はあの日の綺麗な姿のままだ\nこれであの日のように幸せに暮らせる\n\n□月○日\nあれは私の妻ではない\n私はただ化け物を生み出しただけだったのだ\n明日この屋敷から逃げようと思う\nもしこの日記を読んでいる人がいるのなら\nすぐに逃げることをおすすめする\n\n日記はここで終わっているようだ..." },
	{ false, "本","幼馴染の女が本を読み、内容を教えてくれた。\n本には人を生き返らせる方法が書いてあるようだ。\n方法は単純で、魔法陣の上に死体を乗せるだけらしい。\nただし、蘇った人は銀と光に弱くなってしまうようだ。\n" },
};

/*-------------------------
武器の構造体の宣言
flag = 所持していたらtrue,
部屋にあるならfalse
name = 武器の名前
status = 武器の攻撃力
dice = 攻撃の成功判定の基準
explain = 説明
--------------------------*/
struct Weapon {
	bool flag;
	char* name;
	int status;
	int dice;
	char* explain;
};

/*----------------------
武器の構造体の初期化
weapon[0] = 素手
weapon[1] = 銀パイプ
weapon[2] = ハンマー
weapon[3] = 剣
-----------------------*/
struct Weapon weapon[]{
	{ true, "素手", 0, 1,"素手" },
	{ false, "銀パイプ",20,1,"銀でできているパイプのようだ。" },
	{ false, "ハンマー",40,2 ,"物を壊すときに役立ちそうだ。" },
	{ false, "剣",20,1 ,"とても強そうな剣だ。" },
};

/*---------------------------------------------
部屋の構造体の宣言
item1 = 部屋にあるアイテムのアドレス（ポインタ）
item2 = 〃
weapon = 部屋にある武器のアドレス（ポインタ）
locked = 鍵がかかっているならtrue,
鍵がかかっていないならfalse
name = 部屋名
next = 行き先の部屋のアドレス（ポインタ）
floor = 階数
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
部屋の構造体の初期化
room[0] = 地下室
room[1] = １階
room[2] = ２階
room[3] = 図書室
room[4] = 部屋１
room[5] = 部屋２
room[6] = 部屋３
room[7] = 玄関
---------------------*/
struct Room room[] = {
	{ NULL, NULL, NULL, false, "地下室", NULL, NULL , NULL , NULL , NULL, 0 },
	{ NULL, NULL, NULL, false, "１階　", NULL, NULL , NULL , NULL , NULL, 1 },
	{ NULL, NULL, NULL, false, "２階　", NULL, NULL , NULL , NULL , NULL, 2 },
	{ NULL, NULL, NULL, false, "図書室", NULL, NULL , NULL , NULL , NULL, 1 },
	{ NULL, NULL, NULL, false, "物置　", NULL, NULL , NULL , NULL , NULL, 1 },
	{ NULL, NULL, NULL, false, "寝室　", NULL, NULL , NULL , NULL , NULL, 2 },
	{ NULL, NULL, NULL, false, "宝庫　", NULL, NULL , NULL , NULL , NULL,2 },
	{ NULL, NULL, NULL, false, "玄関　", NULL, NULL , NULL , NULL , NULL, 0 }
};

/*----------------------------------------------------------
主人公の構造体の宣言
HP = 主人公のHP
ATK = 主人公の攻撃力
LightFlag = ライトを持っていたらtrue,
持っていなかったらfalse
LadyFlag = 幼馴染の女性がパーティーにいればtrue,
いなかったらfalse
DefeatFlag = 化け物を倒したらtrue,
倒してなかったらfalse
Location = 主人公の現在地のアドレス（ポインタ）
weapon = 主人公の装備している武器のアドレス（ポインタ）
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
化け物の構造体の宣言
HP = 化け物のHP
ATK = 化け物の攻撃力
Location = 化け物の現在地のアドレス（ポインタ）
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