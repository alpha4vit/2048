//
//text::text(string text, Vector2f position, int letterSize)
//{
//	this->font = Font();
//	this->font.loadFromFile("ofont.ru_Bowler.ttf");
//	this->msg = Text(text, this->font, letterSize);
//	if (text == "GAME OVER") {
//		this->msg.setFillColor(Color::Red);
//	}
//	else {
//		this->msg.setFillColor(Color(117, 117, 117));
//	}
//	this->msg.setStyle(Text::Style::Bold);
//	this->msg.setPosition(position);
//}
//
//bool text::isMouseOver(RenderWindow& window)
//{
//	int sizeX = 320;
//	int sizeY = 64;
//	if (this->msg.getString() == "PLAY  AGAIN") {
//		sizeX = 704;
//	}
//	else if (this->msg.getString() == "GAME OVER") {
//		sizeX = 945;
//		sizeY = 105;
//	}
//	Vector2i mousePos = Mouse::getPosition(window);
//	if (mousePos.x > this->msg.getPosition().x && mousePos.x < this->msg.getPosition().x + sizeX
//		&& mousePos.y > this->msg.getPosition().y && mousePos.y < this->msg.getPosition().y + sizeY)
//		return true;
//	else
//		return false;
//}
//
//text text::selected(text text)
//{
//	text.msg.setScale(*new Vector2f(1.10, 1.10));
//	if (text.msg.getString() == "GAME OVER") {
//		text.msg.setFillColor(Color::Yellow);
//	}
//	else {
//		text.msg.setScale(*new Vector2f(1.10, 1.10));
//		text.msg.setFillColor(Color::Black);
//	}
//	return text;
//}
