//
//	DialogLayer.h
//
//	TowerWar
//
//	Create by wang2 on	17-1-23
//
#ifndef __TowerWar_DialogLayer__
#define __TowerWar_DialogLayer__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace rapidjson;

class DialogLayer : public cocos2d::Layer
{
public:

	static DialogLayer*createWithJsonFile(const char*fileName);

	virtual bool init(std::string str);
	void MultUpdate(float dt);
	void getDateByIndex(int index);
	void showAllContent();
	void initStudioUI(const char*jsonFile);
	void touchDownAction(Ref*sender, Widget::TouchEventType controlEvent);
	void pushChineseStr(std::string str, std::vector<std::string>&strVector);
private:
	bool _isOver;
	int index;

	std::string conversation;
	std::vector<std::string>_conVector;

	Text*speetch;
	Text *name;
	ImageView*icon;

	std::string mStr;
	std::string tempStr;
	std::vector<std::string>strVector;
	int vecLength;
};

#endif 
