#include "functions.h"

void ShowError(char * title, string message, string log, bool show_sdl_error){
        string error_string = "";
        if (show_sdl_error){
            error_string = SDL_GetError();
        }
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, (message + error_string).c_str(), NULL);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, (log + error_string).c_str());
}

vector<string> split(string const & word, char delim){
    vector<string> strings;
    stringstream s(word);
    string w;
    while (getline(s, w, delim)){
        strings.push_back(w);
    }

    return strings;
}

LevelScene * CreateScene(SpriteCache * cache,Framebuffer * framebuffer, TextCache * text_cache,Player * player, string filepath){
    LevelScene * scene = new LevelScene(cache->renderer,framebuffer ,cache, text_cache);
    ifstream level_file(filepath.c_str());
    string line;
    string obj_name;
    string obj_filepath;
    if (level_file.is_open()){
        while (getline(level_file, line)){

            vector<string> section = split(line, '|');
            cout << section[0] << endl;

            if (section[0] == "*"){
                vector<string> subsect = split(section[1], ':');
                obj_name = subsect[0];
                obj_filepath = subsect[1];
            }
            else if (section[0] == "+"){
                vector<string> obj_info_list = split(section[1], ',');
                for (auto obj_info: obj_info_list){
                    vector<string> obj_xywh = split(obj_info, '-');
                    if (obj_xywh.size() < 4){}
                    else {
                        int x = stoi(obj_xywh[0]);
                        int y = stoi(obj_xywh[1]);
                        int w = stoi(obj_xywh[2]);
                        int h = stoi(obj_xywh[3]);

                        if (obj_name == "player"){
                            player->Reset();
                            player->SetPos(x, y);
                            player->d_rect.w = w;
                            player->d_rect.h = h;

                            scene->AddPlayer(player);
                        }
                        else if (obj_name == "enemy1"){
                            scene->AddEnemy(new Blinky(cache, x, y, w, h, obj_filepath, "blinky",player));
                        }
                        else if (obj_name == "enemy2"){
                            scene->AddEnemy(new Pinky(cache, x, y, w, h, obj_filepath, "pinky",player));
                        }
                        else if (obj_name == "enemy3"){
                            scene->AddEnemy(new Inky(cache, x, y, w, h, obj_filepath, "inky",player));
                        }
                        else if (obj_name == "enemy4"){
                            scene->AddEnemy(new Clyde(cache, x, y, w, h, obj_filepath, "clyde",player));
                        }
                        else if (obj_name == "level"){
                            scene->SetBackground(cache, x, y, w, h, obj_filepath);
                        }
                        else if (obj_name == "wall"){
                            scene->walls.push_back(new Sprite(cache, {0, 0, 32, 32}, {x, y, w, h}, obj_filepath));
                        }
                        else if (obj_name == "pellet"){
                            scene->pellets.push_back(new Sprite(cache, {0, 0}, {x, y, w, h}, obj_filepath));
                        }
                        else if (obj_name == "big_pellet"){
                            scene->big_pellets.push_back(new Sprite(cache, {0, 0}, {x, y, w, h}, obj_filepath));
                        }
                    }
                }
            }
        }
        level_file.close();
    }
    return scene;
}