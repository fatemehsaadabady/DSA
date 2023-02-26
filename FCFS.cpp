#include <iostream>
#include <vector>
using namespace std;

class Patient // تعریف کلاس بیمار
{
public:
    void set_patient_info(int number_of_patients); // تابعی برای دریافت مشخصات بیمار
    int patient_no;                                // شماره بیمار
    int patient_arrival_time;                      // زمان رسیدن بیمار
    int heal_time;                                 // زمان مورد نیاز برای درمان
    int death_time;                                // زمان باقی مانده تا مرگ بیمار
};

// ---------------- پروتوتایپ توابع -----------------------------
void empty_beds(int beds[], int number_of_beds);
void FCFS(vector<Patient> patients, int beds[], int number_of_beds);

//--------------------بدنه اصلی ---------------------------------
int main()
{
    vector<Patient> patients; // وکتور برای نگهداری بیماران
    Patient temp;

    // دریافت تعداد تخت های بیمارستان و خالی کردن تخت ها
    int number_of_beds;
    cout << "Etner the number of hospotal beds: ";
    cin >> number_of_beds;
    int beds[number_of_beds];         // تخت های بیمارستان (عدد داخل تخت به معنی مدت زمان باقی مانده تا خالی شدن)
    empty_beds(beds, number_of_beds); // خالی کردن تخت ها

    // دریافت تعداد و مشخصات بیماران
    int number_of_patients;
    cout << "Enter the number of patients: ";
    cin >> number_of_patients;
    for (size_t i = 0; i < number_of_patients; i++)
    {
        temp.set_patient_info(patients.size());
        patients.push_back(temp);
    }

    // اجرای الگوریتم FCFS
    FCFS(patients, beds, number_of_beds);

    return 0;
}

// ------------------------------------------------------------------------------

void FCFS(vector<Patient> patients, int beds[], int number_of_beds)
{
    int avg_wating_time = 0; // برای محاسبه میانگین زمان انتظار
    int time_spent = 0; // زمان انتظار هر فرد تا خالی شدن تخت
    int number_of_dead = 0; //تعداد اقراد فوت شده

    for (int j = 0; j < patients.size(); j++)
    {
        bool in_bed = false; //وضعیت بستری بودن یا نبون هر فرد

        // بروز کردن زمان باقی مانده تا خالی شدن هر تخت به ازای هر فرد
        for (int i = 0; i < number_of_beds; i++)
        {
            if (beds[i] != 0)
            {
                beds[i] -= (patients[j].patient_arrival_time - patients[j - 1].patient_arrival_time);
                if (beds[i] < 0)
                {
                    beds[i] = 0;
                }
            }
            beds[i] += time_spent;
        }
        time_spent = 0;


        
        while (in_bed == false)
        {
            // بستری شدن در صورت بستری نبودن فرد و وحود تخت خالی
            for (int i = 0; i < number_of_beds; i++)
            {

                if (beds[i] == 0 && in_bed == false)
                {
                    beds[i] = patients[j].heal_time;
                    in_bed = true;
                    cout << "patients #" << patients[j].patient_no << "  in bed #" << i + 1 << "   in the minute: " << patients[j].patient_arrival_time + time_spent << endl;
                }
            }
            // محاسبه زمان انتظار بیمار تا خالی شدن تخت
            if (in_bed == false)
            {
                time_spent++;
                for (size_t i = 0; i < number_of_beds; i++)
                {
                    beds[i]--;
                }
                // چک کردن فوت شدن بیمار
                patients[j].death_time--;
                if (patients[j].death_time == 0)
                {
                    cout << "patients #" << patients[j].patient_no << " died" << endl;
                    number_of_dead++;
                    break;
                }
            }
        }
        avg_wating_time += time_spent;
    }

    // چاپ کردن تعداد افراد درمان شده و فوت شده و میانگین زمان انتظار بیماران
    cout << "number of cured: " << patients.size() - number_of_dead << endl;
    cout << "number of dead: " << number_of_dead << endl;
    cout << "average wating time: " << (float)avg_wating_time / (float)patients.size() << endl;
}

// خالی کردن تخت ها
void empty_beds(int beds[], int number_of_beds)
{
    for (int i = 0; i < number_of_beds; i++)
    {
        beds[i] = 0;
    }
}

// دریافت مشخصات بیماران
void Patient::set_patient_info(int number_of_patients)
{

    patient_no = number_of_patients + 1;
    cout << "----------------------" << endl;
    cout << "Enter the patient#" << patient_no << " arrival time: ";
    cin >> patient_arrival_time;
    cout << "Etner the patient#" << patient_no << " heal time: ";
    cin >> heal_time;
    cout << "Etner the patient#" << patient_no << " death time: ";
    cin >> death_time;
    cout << "----------------------" << endl;
}

