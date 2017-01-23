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
	int index = 0;

	getDateByIndex(index);

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

	if (array.IsArray())
	{
		int i = index;
		int j = 0;
		strVector.clear();
		
		if (i>array.Size())
		{
			this->removeFromParent();
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
	}
	tempStr = "";
	//schedule(schedule_selector(DialogLayer::touchDownAction));
}

void DialogLayer::showAllContent(){
	_isOver = true;
	unschedule(schedule_selector(DialogLayer::MultUpdate));
	speetch->setString(mStr.c_str());
}

void DialogLayer::initStudioUI(const char*jsonFile){
	Node*node = GUIReader::getInstance()->widgetFromJsonFile(jsonFile);
	Layout*layout = static_cast<Layout*>(node);
	name = static_cast<Text*>(node->getChildByName("lblName"));
	icon = static_cast<ImageView*>(node->getChildByName("img"));
	speetch = static_cast<Text*>(node->getChildByName("lblText"));

	layout->addTouchEventListener(CC_CALLBACK_2(DialogLayer::touchDownAction, this));

	this->addChild(node);
}

void DialogLayer::touchDownAction(Ref*sender, Widget::TouchEventType controlEvent){
	if (controlEvent == Widget::TouchEventType::ENDED)
	{
		if (_isOver==true)
		{
			index++;
			getDateByIndex(index);
		}
		else
		{

		}
	
	}
}