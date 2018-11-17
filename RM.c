#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Task{
  int period;
  int WCET;
  int running;
  string name;
  Task(string n, int x, int y) : name(n), period(x), WCET(y), running(0) {}
};


int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Returns LCM of array elements
int findlcm(vector<int> arr, int n)
{
    // Initialize result
    int ans = arr[0];

    // ans contains LCM of arr[0], ..arr[i]
    // after i'th iteration,
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));

    return ans;
}

vector<Task>  sort_Tasks(vector<Task> Tasks){
  for (int i = 0; i < Tasks.size(); i++)
{
    for (int j = i + 1; j < Tasks.size(); j++)
    {
        if (Tasks[i].period > Tasks[j].period)
        {
          Task a =  Tasks[i];
            Tasks[i] =  Tasks[j];
            Tasks[j] = a;
        }
    }
}

return Tasks;
}


 void Handler(vector<Task> Tasks){
    vector<Task> Ordered_Tasks  =  sort_Tasks(Tasks);
    vector <int> periods;
    for (int i = 0; i < Ordered_Tasks.size(); i++)
      periods.push_back(Ordered_Tasks[i].period);
    int Hyber_Period = findlcm(periods, periods.size());
    cout << "Hyber_Period: " << Hyber_Period << endl;

    cout << "==============================================" << endl;
    int j = 0;
    for (int i = 0; i < Hyber_Period; i++){
        for (int k = 0; k < Ordered_Tasks.size(); k++){
        if (i % Ordered_Tasks[k].period == 0 && i != 0){
          if (Ordered_Tasks[k].running != Ordered_Tasks[k].WCET){
            cout << endl;
            cout << "Missed the deadline for " << Ordered_Tasks[k].name << endl;
            return;
          }
          else
          Ordered_Tasks[k].running = 0;


          }
        }

        for (int k = 0; k < Ordered_Tasks.size(); k++){
        if (i % Ordered_Tasks[k].period == 0 && Ordered_Tasks[k].period < Ordered_Tasks[j].period ){
          Ordered_Tasks[k].running = 0;
            j = k;
            break;
          }
        }
      //  cout << i << j;

        if (Ordered_Tasks[j].running < Ordered_Tasks[j].WCET){
          Ordered_Tasks[j].running++;
        //  cout<< Ordered_Tasks[j].name<< " " << Ordered_Tasks[j].running <<  endl;
        cout<< Ordered_Tasks[j].name<< " -> ";
        }

        else if (j == Ordered_Tasks.size() -1 && Ordered_Tasks[j].running == Ordered_Tasks[j].WCET){
          cout << "idle -> ";
        //  Ordered_Tasks[j].running = 0;
        }

        else {
          bool flag = true;
          int r;
          for (int i = 0; i < Ordered_Tasks.size(); i++){
                if (Ordered_Tasks[i].running < Ordered_Tasks[i].WCET ){
                  flag = false;
                  r = i;
                  break;
                }
              }
          if (flag){
              cout << "idle -> ";
          }
          else{
        //    cout << "yes";
      //    Ordered_Tasks[j].running = 0;
          Ordered_Tasks[r].running++;
          cout<< Ordered_Tasks[r].name<< " -> ";
          j++;
        }
        }

    }


}



int main(){

vector<Task> Tasks;

Task a("T1", 6, 2);
Task b("T2", 8, 2);
Task c("T3", 12, 2);

/*
Task a("First", 5, 3);
Task b("Second", 8, 1);
Task c("Third", 10, 1);
*/
/*
Task a("T1", 4, 1);
Task b("T2", 6, 2);
Task c("T3", 10, 3);
/*
Task a("T1", 4, 1);
Task b("T2", 6, 2);
Task c("T3", 8, 3);
*/

Tasks.push_back(a);
Tasks.push_back(b);
Tasks.push_back(c);

Handler(Tasks);

}
