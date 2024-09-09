#include <bits/stdc++.h>

#define int long long
using namespace std;

int dp(int power, int index, int skip, int recharge, int iniPower, vector<int> &enemy, vector<vector<vector<vector<int>>>> &mem) {
	if (index > 10) return 1;
	
	// checking if the answer of this sub-problem is already stored in 'mem' or not. If it is stored, simply returning the answer.
	if (power >= 0 && power < mem.size() && index <= 10 && skip < mem[0][0].size() && recharge < mem[0][0][0].size()) {
        if(mem[power][index][skip][recharge] != -1)
            return mem[power][index][skip][recharge];
    } else {
        return 0;  
    }

	int answer = 0;
	// if Abhimanyu wants to fight current and he is actually worthy enough
	if (power - enemy[index] > 0) {
		// if the back enemy doesn't want to fight because he is scared of Abhimanyu
		answer |= dp(power - enemy[index], index + 1, skip, recharge, iniPower, enemy, mem);

		if (index == 3 || index == 7) {
			// if the back enemy wants to fight and Abhimanyu wants to fight him too and he is actually worthy enough
			if (power - enemy[index] - (enemy[index - 1] >> 1) > 0) answer |= dp(power - enemy[index] - (enemy[index - 1] >> 1), index + 1, skip, recharge, iniPower, enemy, mem);

			// if the back enemy wants to fight but Abhimanyu wants to skip him
			if (skip) answer |= dp(power - enemy[index], index + 1, skip - 1, recharge, iniPower, enemy, mem);

			// if the back enemy wants to fight but Abhimanyu is not worthy enough but will become worthy after a quick recharge
			if (recharge && (power - enemy[index] - (enemy[index - 1] >> 1) + iniPower) > 0) answer |= dp(power - enemy[index] - (enemy[index - 1] >> 1) + iniPower, index + 1, skip, recharge - 1, iniPower, enemy, mem);
		}
	}

	// if Abhimanyu doesn't want to fight current because he is bored
	if (skip) {
		// if the back enemy also doesn't want to fight because he is scared of Abhimanyu
		answer |= dp(power, index + 1, skip - 1, recharge, iniPower, enemy, mem);

		if (index == 3 || index == 7) {
			// if the back enemy wants to fight and Abhimanyu wants to fight him too beacause he too bored without work
			if (power - (enemy[index - 1] >> 1) > 0) answer |= dp(power - (enemy[index - 1] >> 1), index + 1, skip - 1, recharge, iniPower, enemy, mem);

			// if the back enemy wants to fight but Abhimanyu wants to skip him. 
			if (skip > 1) answer |= dp(power, index + 1, skip - 2, recharge, iniPower, enemy, mem);

			// if the back enemy wants to fight but Abhimanyu is not worthy enough but will become worthy after a quick recharge
			if (recharge && (power - (enemy[index - 1] >> 1) + iniPower) > 0) answer |= dp(power - (enemy[index - 1] >> 1) + iniPower, index + 1, skip-1, recharge - 1, iniPower, enemy, mem);
		}
	}

	// if Abhimanyu is not worthy enough but will become worthy after a quick recharge
	if (recharge && (power - enemy[index] + iniPower > 0)) {
		// if the back enemy also doesn't want to fight because he is scared of Abhimanyu
		answer |= dp(power - enemy[index] + iniPower, index + 1, skip, recharge - 1, iniPower, enemy, mem);

		if (index == 3 || index == 7) {
			// if the back enemy wants to fight and Abhimanyu wants to fight him too because he too strong after charging
			if (power - enemy[index] + iniPower - (enemy[index - 1] >> 1) > 0) answer |= dp(power - enemy[index] + iniPower - (enemy[index - 1] >> 1), index + 1, skip, recharge - 1, iniPower, enemy, mem);

			// if the back enemy wants to fight but Abhimanyu wants to skip him.
			if (skip) answer |= dp(power - enemy[index] + iniPower, index + 1, skip - 1, recharge - 1, iniPower, enemy, mem);

			// if the back enemy wants to fight but Abhimanyu is still not worthy enough but will become worthy after a quick recharge 
			if (recharge > 1 && (power - enemy[index] - (enemy[index - 1] >> 1) + 2 * iniPower) > 0) answer |= dp(power - enemy[index] - (enemy[index - 1] >> 1) + 2 * iniPower, index + 1, skip, recharge - 2, iniPower, enemy, mem);
		}
	}

    // Storing the answer for this sub-problem to use it in future without calculating it again.
	return mem[power][index][skip][recharge] = answer;
}

int32_t main() {

	int power, skip, recharge, iniPower;
	vector<int> enemy(11);
	cin >> power >> skip >> recharge;
	
	iniPower = power;
	
    // This will store the answer for the sub-problems to use it in future without calculating it again.
	vector<vector<vector<vector<int>>>> mem(max(power, (power*recharge)) + 1, vector<vector<vector<int>>>(11, vector<vector<int>>(skip + 1, vector<int>(recharge + 1, -1))));

	for (int i = 0; i < 11; i++) cin >> enemy[i];

	if(dp(power, 0, skip, recharge, iniPower, enemy, mem))
	    cout << "Abhimanyu can cross the Chakrvyuha" << endl;
	else
	    cout << "Abhimanyu cannot cross the Chakrvyuha" << endl;
	return 0;
}


//Test case: 1 


// enemyPower = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110}
// power = 100
// a = 5 
// b = 5
// Answer: Abhimanyu can cross the Chakrvyuha

// Input Format:

// 100 5 5 
// 10 20 30 40 50 60 70 80 90 100 110


//Test case: 2


// enemyPower = {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 7}
// power = 5
// a = 3 
// b = 5
// Answer: Abhimanyu cannot cross the Chakrvyuha

// Input Format:

// 5 3 5
// 0 10 2 3 9 5 6 7 8 4 7