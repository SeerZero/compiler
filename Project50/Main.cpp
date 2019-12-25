#include"run.h"
int main() {
	run runner;
	runner.syn.ct.save_list();
	runner.syn.syn();
	//runner.syn.youhua();
	cout << endl << endl;
	runner.syn.scanner.show();
	cout << endl << endl;
	runner.syn.show();
	cout << endl << endl;
	cout << "Ä¿±ê´úÂë" << endl;
	runner.add_bool();
	runner.Begin();
	runner.read();
	runner.all_ten_to_sixteen();
	runner.huibian();
}