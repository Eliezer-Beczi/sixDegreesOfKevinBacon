#include "graphReader.h"
#include "dynamicQueue.h"

#define infinity -1

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::ifstream;
using std::exception;
using std::unordered_map;
using std::invalid_argument;

// Beolvassuk a ket szineszt, akik kozott keressuk a legrovidebb utat
template <class A>
void beOlvas(A &u, A &v, const char * const file) {
	ifstream inputFile(file);

	inputFile >> u;
	inputFile >> v;
}

// Kiirjuk a kepernyore a legrovidebb utat, s ennek hosszat
template <class A>
void kiIr(A const &u, A const &v, const int& length, const dQueue<A>& path) {
	cout << "(Actor 1) " << u << " <---> " << v << " (Actor 2)" << endl;
	cout << u << " -> " << v << " : " << length << endl;

	for(unsigned i = 1; i  < path.size(); i+= 2) {
		cout << path[i - 1] << " was in " << path[i] << " with " << path[i + 1] << endl;
	}
}

// Fuggveny, amely leellenorzi, hogy fellelheto-e a ket szinesz a grafban
template <class A, class B>
void check(const list<A, B>& G, A const& u, A const& v) {
	if(G.find(u) == G.end()) {
		throw invalid_argument("Nincs ilyen szinesz: " + u);
	}

	if(G.find(v) == G.end()) {
		throw invalid_argument("Nincs ilyen szinesz: " + v);
	}
}

// Moore algoritmusa => meghatarozza a legrovidebb utat a ket szinesz kozott
template <class A, class B>
pair<unordered_map<A, B>, unordered_map<A, A>> MooreDistance(const list<A, B>& G, A const &u) {
	dQueue<A> dq;
	unordered_map<A, B> l;
	unordered_map<A, A> p;

	for(auto& m : G) {
		l[m.first] = infinity;
	}

	l[u] = static_cast<B>(0);

	dq.push(u);

	while(!dq.empty()) {
		A x = dq.front();
		auto it = G.find(x);

		if(it != G.end()) {
			for(auto& m : (*it).second) {
				A y = m.first;

				if(l[y] == infinity) {
					p[y] = x;
					l[y] = l[x] + static_cast<B>(m.second);
					dq.push(y);
				}
			}
		}

		dq.pop();
	}

	return make_pair(l, p);
}

// Felepitjuk az utvonalat
template <class A, class B>
dQueue<A> MoorePath(const B& length, const unordered_map<A, A>& p, A const &u, A const &v) {
	if(length == infinity) {
		return dQueue<A>();
	}

	dQueue<A> path;
	path.push(v);

	A back = v;

	while(back != u) {
		path.push(p.at(back));
		back = path.back();
	}

	path.reverse();

	return path;
}

// Vezerlofuggveny
template <class A, class B>
void logic(const char * const file_1 = "graf.txt", const char * const file_2 = "szineszek.txt") {
	list<A, B> G = graphReader::adjacencyList<A, B>(file_1, 1);
	// cout << G << endl;

	A u;
	A v;

	beOlvas(u, v, file_2);

	try {
		check(G, u, v);
	}
	catch (const exception& e) {
		throw;
	}

	pair<unordered_map<A, B>, unordered_map<A, A>> result = MooreDistance<A, B>(G, u);
	dQueue<A> path = MoorePath<A, B>(result.first[v], result.second, u, v);
	kiIr<A>(u, v, result.first[v], path);
}

int main(int argc, char const *argv[])
{
	try {
		logic<string, int>();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	return 0;
}
