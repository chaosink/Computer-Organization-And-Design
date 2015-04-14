#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

extern int font_number;
extern char font_code[1000];

void pinyin2code(char *py) {
	string spy = py;
	vector<string> vpy = {"a","ai","an","ang","ao","ba","bai","ban","bang","bao","bei",
	"ben","beng","bi","bian","biao","bie","bin","bing","bo","bu","ca","cai","can",
	"cang","cao","ce","cen","ceng","cha","chai","chan","chang","chao","che","chen",
	"cheng","chi","chong","chou","chu","chua","chuai","chuan","chuang","chui","chun",
	"chuo","ci","cong","cou","cu","cuan","cui","cun","cuo","da","dai","dan","dang",
	"dao","de","den","dei","deng","di","dia","dian","diao","die","ding","diu","dong",
	"dou","du","duan","dui","dun","duo","e","ei","en","eng","er","fa","fan","fang",
	"fei","fen","feng","fo","fou","fu","ga","gai","gan","gang","gao","ge","gei","gen",
	"geng","gong","gou","gu","gua","guai","guan","guang","gui","gun","guo","ha","hai",
	"han","hang","hao","he","hei","hen","heng","hong","hou","hu","hua","huai","huan",
	"huang","hui","hun","huo","ji","jia","jian","jiang","jiao","jie","jin","jing",
	"jiong","jiu","ju","juan","jue","jun","ka","kai","kan","kang","kao","ke","ken",
	"keng","kong","kou","ku","kua","kuai","kuan","kuang","kui","kun","kuo","la","lai",
	"lan","lang","lao","le","lei","leng","li","lia","lian","liang","liao","lie","lin",
	"ling","liu","long","lou","lu","luan","lue","lun","luo","ma","mai","man","mang",
	"mao","me","mei","men","meng","mi","mian","miao","mie","min","ming","miu","mo",
	"mou","mu","na","nai","nan","nang","nao","ne","nei","nen","neng","ni","nian",
	"niang","niao","nie","nin","ning","niu","nong","nou","nu","nv","nuan","nue","nuo",
	"nun","o","ou","pa","pai","pan","pang","pao","pei","pen","peng","pi","pian","piao",
	"pie","pin","ping","po","pou","pu","qi","qia","qian","qiang","qiao","qie","qin",
	"qing","qiong","qiu","qu","quan","que","qun","ran","rang","rao","re","ren","reng",
	"ri","rong","rou","ru","ruan","rui","run","ruo","sa","sai","san","sang","sao","se",
	"sen","seng","sha","shai","shan","shang","shao","she","shen","sheng","shi","shou",
	"shu","shua","shuai","shuan","shuang","shui","shun","shuo","si","song","sou","su",
	"suan","sui","sun","suo","ta","tai","tan","tang","tao","te","teng","ti","tian",
	"tiao","tie","ting","tong","tou","tu","tuan","tui","tun","tuo","wa","wai","wan",
	"wang","wei","wen","weng","wo","wu","xi","xia","xian","xiao","xiang","xie","xin","xing",
	"xiong","xiu","xu","xuan","xue","xun","ya","yan","yang","yao","ye","yi","yin",
	"ying","yo","yong","you","yu","yuan","yue","yun","za","zai","zan","zang","zao",
	"ze","zei","zen","zeng","zha","zhai","zhan","zhang","zhao","zhe","zhen","zheng",
	"zhi","zhong","zhou","zhu","zhua","zhuai","zhuan","zhuang","zhui","zhun","zhuo",
	"zi","zong","zou","zu","zuan","zui","zun","zuo"};
	vector<int> sht = {5,25,19,3,24,28,12,22,14,27,28,8,11,60,29,17,5,15,16,33,19,3,
		11,12,7,11,7,2,5,25,8,28,26,15,8,22,32,46,13,22,30,0,5,16,6,8,14,11,22,13,5,
		10,7,15,5,14,17,24,26,11,21,5,0,0,13,35,1,27,18,21,20,2,20,16,24,10,8,15,19,
		35,1,4,0,15,10,25,17,31,21,20,1,2,77,9,12,24,14,20,34,1,6,10,22,22,46,10,5,
		21,6,34,8,21,3,12,30,7,18,30,2,4,7,16,15,43,16,7,31,24,39,11,19,111,40,71,22,
		45,39,35,44,6,28,55,18,30,15,6,13,14,9,8,28,8,5,8,10,12,5,9,3,16,23,10,5,13,
		13,25,15,18,8,20,5,79,0,29,16,18,11,20,26,23,17,13,55,9,3,8,22,17,9,18,12,28,
		1,27,8,19,31,17,16,7,12,9,1,27,8,20,13,9,9,6,12,3,2,3,1,23,13,2,6,13,1,10,7,
		5,1,8,4,1,0,8,0,2,13,9,8,14,7,12,15,3,17,34,10,8,4,11,12,14,1,24,69,4,42,20,
		25,11,22,20,6,23,28,19,10,3,7,7,6,3,18,2,1,15,6,18,3,7,2,2,7,5,8,6,9,7,1,1,
		15,3,31,12,20,19,24,15,67,14,47,4,5,3,4,5,5,10,35,16,12,19,3,16,9,13,13,16,
		23,24,15,3,5,23,13,9,5,14,19,6,15,4,7,6,21,10,4,27,15,60,16,6,14,51,68,19,41,
		29,29,34,15,19,8,18,29,27,9,26,27,64,25,29,21,92,28,36,2,23,36,76,29,13,20,6,
		10,10,5,15,13,1,1,6,22,7,19,23,15,18,26,19,69,16,23,44,1,2,7,9,8,2,16,33,9,5,
		9,5,4,5,10};
	auto index = find(vpy.begin(), vpy.end(), spy);
	if(index == vpy.end()) {
		font_number = 0;
		return;
	}
	int dis = distance(vpy.begin(), index);
	int sum = 0;
	for(int i = 0; i < dis; i++) {
		sum += sht[i];
	}
	sum *= 2;
	font_number = sht[dis];
	ifstream fin;
	fin.open("data/pydata.data");
	fin.seekg(sum, ios::beg);
	fin.read(font_code, font_number * 2);
	fin.close();
}
