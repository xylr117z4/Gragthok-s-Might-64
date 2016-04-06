void moveTo(std::tuple<int, int> newPos, bool& move){
	if(distanceBetween(objectPos, newPos) <= 1){
		move = false;
	}
	else{
		int x = object.pos.x - newPos.x;
		int y = object.pos.y - newPos.y;
		float direction = atan2(x, y);
		object.move(sin(direction)*speed, cos(direction)*speed);
	}
}
