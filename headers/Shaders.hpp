#ifndef Shaders_hpp
#define Shaders_hpp

using namespace std;

class Shader {
public:
	string name;
	sf::Shader* shader;

	Shader(string pathfile) {

		name = "";
		
		int i = int(pathfile.size()) - 6;
		while (i >= 0)
			name = pathfile[i--] + name;

		cout << name;

		shader = new sf::Shader();
		shader->loadFromFile("assets/" + pathfile, sf::Shader::Fragment);
		//cout << "load shader: " << pathfile << " as: " << name << endl;
	}

};

std::vector < Shader* > shaders;

void loadShader(string pathfile) {
	shaders.push_back(new Shader(pathfile));
}

void loadShaders() {

	loadShader("shaders/water.frag");
	loadShader("shaders/circle.frag");
	loadShader("shaders/jagged_circle.frag");
	loadShader("shaders/circles.frag");
}

Shader* getShader(string name) {

	for (auto& s : shaders) {
		if (s->name == name) {
			return s;
		}
	}

	std::cout << "error - get Shader - Shader: \"" << name << "\" not exists\n";
	return nullptr;
}



#endif // !define Shaders_hpp
