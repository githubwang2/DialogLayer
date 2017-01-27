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
	//将某一个对话的内容保存在容器中
	void getDateByIndex(int index);
	//显示所有文字 
	void showAllContent();
	//加载cocostudio的ui
	void initStudioUI(const char*jsonFile);
	//案件回调
	void touchDownAction(Ref*sender, Widget::TouchEventType controlEvent);
	void pushChineseStr(std::string str, std::vector<std::string>&strVector);
private:
	
	bool _isOver;							//	字符串是否完全显示
	int m_index;								//	数组下标

	std::string conversation;				//	json中的字符串
	std::vector<std::string>_conVector;		//	每个对话的数组 
											//	数组中3个内容 人物图片 人物名字 对话
	Text*speetch;							//	对话内容		
	Text *name;								//	人物名字
	ImageView*icon;							//	人物头像 

	std::string mStr;
	std::string tempStr;					//	
	std::vector<std::string>strVector;		//每个元素都是1个汉字
	int vecLength;							//容器的长度

	Node*node;
};

#endif 
