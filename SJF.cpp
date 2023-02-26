#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Patient // تعریف کلاس بیمار
{
public:
    void set_patient_info(int number_of_patients); // تابعی برای دریافت مشخصات بیمار
    int patient_no;                                // شماره بیمار
    int patient_arrival_time;                      // زمان رسیدن بیمار
    int patient_heal_time;                         // زمان مورد نیاز برای درمان
    int patient_death_time;                        // زمان باقی مانده تا مرگ بیمار
};

// ---------------- پروتوتایپ توابع -----------------------------

bool heal_time_sort(Patient first, Patient second);
bool arrival_time_sort(Patient first, Patient second);

//--------------------بدنه اصلی ---------------------------------
int main()
{
    vector<Patient> patients; // وکتور برای نگهداری بیماران
    Patient temp;

    // دریافت تعداد و مشخصات بیماران
    int number_of_patients;
    cout << "Enter the number of patients: ";
    cin >> number_of_patients;
    for (size_t i = 0; i < number_of_patients; i++)
    {
        temp.set_patient_info(patients.size());
        patients.push_back(temp);
    }

    // مرتب سازی بیماران براساس طول درمان و زمان ورود
    sort(patients.begin(), patients.end(), heal_time_sort);
    sort(patients.begin(), patients.end(), arrival_time_sort);

    int total_time = 0;                     // کل زمان صرف شده
    int visit_time[number_of_patients + 1]; // ثانیه ای که نوبت بیمار میرسد
    bool is_dead[number_of_patients];       // زنده بودن یا فوت شدن بیمار
    int number_of_dead = 0;                 // تعداد افراد فوت شده

    // مفداری دهیه اولیه وضعیت زنده بودن بیماران
    for (int i = 0; i < number_of_patients; i++)
    {
        is_dead[i] = false;
    }

    //محاسبه ترتیب بستری بیماران بر اساس طول زمان درمانس
    for (int i = 0; i < number_of_patients; i++)
    {
        int j = i;
        while (patients[j].patient_arrival_time <= total_time && j <= number_of_patients)
        {
            j++;
        }
        sort(patients.begin() + i, patients.begin() + j, heal_time_sort);
        visit_time[i] = total_time;
        if (visit_time[i] - patients[i].patient_arrival_time >= patients[i].patient_death_time)
        {
            is_dead[i] = true;
            number_of_dead++;
        }
        else
        {

            total_time += patients[i].patient_heal_time;
        }
    }
    visit_time[number_of_patients] = total_time; // زمان پایان
    float avg_wating_time = 0; // برای محاسبه میانگین زمان انتظار بیماران

    // محاسبه و چاپ شماره بیمار - زمان ورود - طول زمان درمان - زمان رسیدن نوبت - زمان انتظار
    cout << "pno\tArrival time\tHeal time\tCurrent time\tWating time" << endl;
    for (int i = 0; i < number_of_patients; i++)
    {
        cout << patients[i].patient_no << "\t\t";
        cout << patients[i].patient_arrival_time << "\t\t";
        cout << patients[i].patient_heal_time << "\t\t";
        cout << visit_time[i] << "\t\t";
        avg_wating_time += visit_time[i] - patients[i].patient_arrival_time;
        cout << visit_time[i] - patients[i].patient_arrival_time << '\t';
        if (is_dead[i] == true)
        {
            cout << "*DIED*";
        }
        cout << endl;
    }

    // چاپ نمودار زمانی
    cout << "\nTime Chart\n";
    for (int i = 0; i < number_of_patients; i++)
    {
        if (is_dead[i] == false)
        {
            cout << "|   " << patients[i].patient_no << "   |";
        }
    }

    cout << "\n";
    for (int i = 0; i < number_of_patients + 1; i++)
    {
        if (is_dead[i] == false)
        {
            cout << visit_time[i] << "\t";
        }
    }
    // چاپ تعداد افراد فوت شده و درمان شده و میانگین زمان انتظار
    cout << "\n";
    cout << "number of cured: " << number_of_patients - number_of_dead << endl;
    cout << "number of dead: " << number_of_dead << endl;
    cout << "Average Waiting time: " << (float)avg_wating_time / (float)number_of_patients << endl;

    return 0;
}

// تابع شرط مرتب سازی بر اساس زمان درمان
bool heal_time_sort(Patient first, Patient second)
{
    return first.patient_heal_time < second.patient_heal_time;
}

// تابع شرط مرتب سازی بر اساس زمان ورود
bool arrival_time_sort(Patient first, Patient second)
{
    return first.patient_arrival_time < second.patient_arrival_time;
}

// دریافت مشخصات بیماران
void Patient::set_patient_info(int number_of_patients)
{
    patient_no = number_of_patients + 1;
    cout << "----------------------" << endl;
    cout << "Enter the patient#" << patient_no << " arrival time: ";
    cin >> patient_arrival_time;
    cout << "Etner the patient#" << patient_no << " heal time: ";
    cin >> patient_heal_time;
    cout << "Etner the patient#" << patient_no << " death time: ";
    cin >> patient_death_time;
}