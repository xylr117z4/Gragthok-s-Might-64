void loadMap(std::string mapName){
	bool scanMap = true;
	int i = 0;
	int c = 0;
	std::stringstream ss;
	std::vector<std::vector<std::string>> tileList;
	tileList.push_back();
	
	orxConfig_push(mapName.c_str());
	
	while(scanMap){
		ss.str("");
		ss << c;
		
		orxSTRING tileName = orxConfig_GetListString(ss.str().c_str(), i);
		
		if(orxString_Compare(tileName, "End") == 0){
			tileList.push_back();
			c++;
			
			orxSTRING firstTileName = orxConfig_GetListString(ss.str().c_str(), 0);
			
			if(orxString_Compare(firstTileName, "End") == 0){
				scanMap = false;
			}
		}
		else{
			tileList[c].push_back(tileName);
		}
		
		++i;
	}
	
	orxConfig_pop();
}

	std::stringstream ss;
	std::vector<std::vector<std::string>> tileList;
	std::vector<std::vector<std::string>> origin = { { "1", "2", "3", "End" }, { "5", "6", "7", "End" }, { "9", "10", "11", "End" }, { "13", "14", "15", "End" }, {"End"} };
	bool scanMap = true;
	int i = 0;
	int c = 0;
	tileList.emplace_back();

	while (scanMap){
		ss.str("");
		ss << c;
		
		std::string tileName = origin[c][i];

		if (tileName == "End"){
			c++;
			i = 0;

			std::string firstTileName = origin[c][i];

			if (firstTileName == "End"){
				scanMap = false;
			}
			else{
				tileList.emplace_back();
			}
		}
		else{
			tileList[c].push_back(tileName);
			++i;
		}
		
	}
	for (int i = 0; i < tileList.size(); ++i){
		for (int c = 0; c < tileList[0].size(); ++c){
			std::cout << tileList[i][c] << ", ";
		}
		std::cout << "\n";
	}