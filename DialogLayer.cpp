#include"DialogLayer\DialogLayer.h"

void DialogLayer::pushChineseStr(std::string str, std::vector<std::string>&strVector){
	int sum = strlen(str.c_str());
	for (int  cur = 0; cur < sum; )
	{
		std::string lines;
		char t = str[cur];
		if ((t&0xE0)==0xE0)				//1110 0000 
		{
			lines = lines + t + str[cur + 2];
			cur += 3;
		}
		else if ((t & 0xC0) == 0xC0)	//2 byte
		{
			lines = lines + t + str[cur + 1];
			cur += 1;
		}
		{
			lines = lines + t ;
			cur ++;
		}

	}

}

DialogLayer*DialogLayer::createWithJsonFile(const char*fileName){
	DialogLayer*dialogLayer = new DialogLayer();
	if (dialogLayer && dialogLayer->init(fileName))
	{
		dialogLayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(dialogLayer);
	}
	return dialogLayer;
}

bool DialogLayer::init(std::string str){
	initStudioUI("DialogLayer/DialogLayer.json");
	
	conversation = FileUtils::getInstance()->getStringFromFile(str);
	m_index = 0;
	vecLength = 0;
	getDateByIndex(m_index);

	return true;
}

void DialogLayer::MultUpdate(float dt){
	if (vecLength<(int)strVector.size())
	{
		tempStr = tempStr + strVector[vecLength].c_str();
		speetch->setString(tempStr.c_str());
		vecLength++;
	}
	else
	{
		_isOver = true;
		unschedule(schedule_selector(DialogLayer::MultUpdate));
	}
}

void DialogLayer::getDateByIndex(int index){
	Document doc;
	doc.Parse<kParseDefaultFlags>(conversation.c_str());
	_conVector.clear();
	_isOver = false;
	rapidjson::Value & array = doc["Conversation"];
	//array是不是数组
	if (array.IsArray())
	{
		int i = index;
		int j = 0;
		strVector.clear();
		
		if (i>=array.Size())		//	说明已经显示完全
		{
			CCLOG("显示完全 开始游戏内容");
			this->removeFromParent();
			//node->removeFromParent();
			return;
		}
		for (j = 0; j < array[i]["content"].Size(); j++)
		{
			rapidjson::Value &str = array[i]["content"][j];
			mStr = str.GetString();
			CCLOG("test str %s", mStr.c_str());
			_conVector.push_back(str.GetString());
			if (j==2)
			{
				pushChineseStr(mStr, strVector);
			}
		}
		name->setString(_conVector[0]);
		icon->loadTexture(_conVector[1]);
		speetch->setString(_conVector[2]);
	}
	//tempStr = "";
	
	schedule(schedule_selector(DialogLayer::MultUpdate));
}

void DialogLayer::showAllContent(){
	_isOver = true;
	unschedule(schedule_selector(DialogLayer::MultUpdate));
	speetch->setString(mStr.c_str());
}

void DialogLayer::initStudioUI(const char*jsonFile){
	node = GUIReader::getInstance()->widgetFromJsonFile(jsonFile);
	Layout*layout = static_cast<Layout*>(node);
	name = static_cast<Text*>(node->getChildByName("lblName"));
	icon = static_cast<ImageView*>(node->getChildByName("imgPlayer"));
	speetch = static_cast<Text*>(node->getChildByName("lblText"));

	layout->addTouchEventListener(CC_CALLBACK_2(DialogLayer::touchDownAction, this));

	this->addChild(node);
}

void DialogLayer::touchDownAction(Ref*sender, Widget::TouchEventType controlEvent){
	if (controlEvent == Widget::TouchEventType::ENDED)
	{
		CCLOG("1");
		if (_isOver==true)
		{
			m_index++;
			getDateByIndex(m_index);
			CCLOG("2");
		}
		else
		{
			CCLOG("3");
			this->showAllContent();
		}
	
	}
}