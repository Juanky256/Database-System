#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>

using namespace std;

//Function for opening all file
int open_file(ifstream &in_file, string file_name, int size = 0){
    in_file.open(file_name);
    if (!in_file) {
        cout << "Error opening file " << endl;
        cin.ignore();
        exit(1);
    }
    in_file >> size;
    return size;
}

//Function for reading all files and sending the information to a vector
 vector<vector<string>> read_file(ifstream &in_file, vector<vector<string>> vec) {
     string file_line;
     string data;
     getline(in_file, data);                    //Moving cursor to next line in file
     while(getline(in_file, file_line))         //Getting all the data and putting it in the vector
    {
        size_t start = 0;
        vector<string> vec2;
        while(true) {
            size_t ind = file_line.find("#", start);  //Finding the different strings from file
            
            if (ind == -1)
            {
                data = file_line.substr(start, file_line.find('\n'));
                vec2.push_back(data);
                break;
            }
            if (start == 0)
            {
                data = file_line.substr(start, ind);
                vec2.push_back(data);
            }
            else
            {
                data = file_line.substr(start, ind-start);
                vec2.push_back(data);
            }
        
            start = ind+1;
        }
        vec.push_back(vec2);
    }
     return vec;
}

//Function for printing employees' data
void print_employee(vector<vector<string>> vec, int size) {
    cout << setw(4) << "ID" << setw(12) << "Name" << setw(12) << "Surname"
    << setw(15) << "Salary($)" << setw(55) << "E-mail Address" << setw(15) << "Birth Date\n\n";
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 6; j++)
            switch(j){
                case 0:
                    cout << setw(4) << vec[i][j];
                    break;
                case 1:
                    cout << setw(12) << vec[i][j];
                    break;
                case 2:
                    cout << setw(12) << vec[i][j];
                    break;
                case 3:
                    cout << setw(15) << vec[i][j];
                    break;
                case 4:
                    cout << setw(55) << vec[i][j];
                    break;
                case 5:
                    cout << setw(15) << vec[i][j];
                    break;
                    
            }
    cout << endl;
    }
    cout << "\n";
       
}

int main()
{
    ifstream employee_file;             //File declarations
    ifstream department_file;
    ifstream manages_file;
    ifstream projects_file;
    ifstream works_for_file;
    ifstream works_on_file;
    int choice;
    int sizes[6];
    string files[6] = {"employees.txt", "departments.txt", "manages.txt", "projects.txt", "works_for.txt", "works_on.txt"};
    
    sizes[0] = open_file(employee_file, files[0]);
    sizes[1] = open_file(department_file, files[1]);
    sizes[2] = open_file(manages_file, files[2]);
    sizes[3] = open_file(projects_file, files[3]);
    sizes[4] = open_file(works_for_file, files[4]);
    sizes[5] = open_file(works_on_file, files[5]);
    
    vector<vector<string>> employee_data;       //Vectors for storing all the data
    vector<vector<string>> department_data;
    vector<vector<string>> manages_data;
    vector<vector<string>> projects_data;
    vector<vector<string>> works_for_data;
    vector<vector<string>> works_on_data;
    
    employee_data = read_file(employee_file, employee_data);            //Passing data from files to vectors
    department_data = read_file(department_file, department_data);
    manages_data = read_file(manages_file, manages_data);
    projects_data = read_file(projects_file, projects_data);
    works_for_data = read_file(works_for_file, works_for_data);
    works_on_data = read_file(works_on_file, works_on_data);
    
    cout << "Welcome to Database System for Mushroom Inc, you can access the employee data by choosing a number\n" << endl;
    
    do {
        cout << "1) Print all employees " << endl
             << "2) Print all employees who work for specific department ID" << endl
             << "3) Print all employees with their department " << endl
             << "4) Print all employees who work for a specific department ID and on a specific project " << endl
             << "5) Print salaries of all managers " << endl
             << "6) Print all projects, on which more than 5 employees are working " << endl
             << "7) Exit " << endl
             <<  "\nWhat would you like to do? " << endl;
        cin >> choice;
        cout << endl;
        
        switch (choice){
            case 1:{
                print_employee(employee_data, sizes[0]);
                break;
            }
            case 2:{
                int ID;
                cout << "Enter the department from which you want to print all the employees ";
                cin >> ID;
                
                
                vector<string> vec2;
                
                for (int i = 0; i < sizes[4]; i++){   //Comparing the ID for which the employees work to the
                    if (ID == stoi(works_for_data[i][1])){      //department ID
                        vec2.push_back(works_for_data[i][0]);       //Storing the ID of the workers
                    }
                }
                
                for (auto v: vec2)          //Print the name and surname of the employees' IDs in vec2
                    for (int j = 0; j < sizes[0]; j++){
                        if (v == employee_data[j][0])
                            cout << employee_data[j][1] << " " << employee_data[j][2] << endl;
                    }
                cout << endl;
            }
                break;
            case 3:{
                int num = 0;
                for (int i = 0; i < sizes[0]; i++){
                    cout << employee_data[i][1] << " ";     //Print the employee's name
                    for (int j = 0; j < sizes[4]; j++)
                        if (employee_data[i][0] == works_for_data[j][0])   //Get the ID of department and
                            num = stoi(works_for_data[j][1]);          //compare it to the one in works_for
                                                                        //vector
                    for (int x = 0; x < sizes[1]; x++)
                        if (num == stoi(department_data[x][0]))         //if the departments match print the
                            cout << department_data[x][1] << endl;      //department with the name
                }
                cout << endl;
                break;
            }
            case 4:{
                int dep_ID, pro_ID;
                cout << "Enter the ID number for the Department and Project\n";
                cin >> dep_ID >> pro_ID;
                vector<string> employees;
                vector<string> employees2;
                
                for (int i = 0; i < sizes[4]; i++)
                    if (dep_ID == stoi(works_for_data[i][1]))       //Trying to match IDs to the user input
                        employees.push_back(works_for_data[i][0]);   //Storing IDs of employees when we find
                                                                     //They work in the department
                for (int i = 0; i < sizes[5]; i++)//Look for employees with project ID
                    if (pro_ID == stoi(works_on_data[i][1]))
                        employees2.push_back(works_on_data[i][0]);
                
                for (int i = 0; i < employees.size(); i++)      //Comparing the IDs department to the ID in
                    for (int j = 0; j < employees2.size(); j++)  //employee_data
                        if (employees[i] == employees[j])
                            cout << employee_data[stoi(employees[i])-1][1] << " " << employee_data[stoi(employees[i])-1][2] << endl;
                        
                cout << endl;
                break;
            }
            case 5:{
                for (int i = 0; i < sizes[2]; i++)      //Find names of managers by comparing manages ID to
                    for (int j = 0; j < sizes[0]; j++)     //employee IDs. If they match, print salaries
                        if (manages_data[i][0] == employee_data[j][0])
                            cout << employee_data[j][1] << " " << employee_data[j][2] << ":  $" << employee_data[j][3] << endl;
                cout << endl;
                break;
            }
            case 6: {
                vector<string> projects;        //Create a vector to store the number of project IDs from
                for (int i = 0; i < sizes[3]; i++)      //project_data
                    projects.push_back(projects_data[i][1]);
                
                int x = 1;
                auto it = projects.begin();
        
                for (; it != projects.end(); it++){     //Count in works_on_data and keep the projects with
                    int num = 0;                      //5 or more
                    for (int i = 0; i < 50; i++){
                        if (works_on_data[i][1] == to_string(x))
                            num++;
                    }
                    
                    if (num <= 5)       //Erase the projects with less than 5 people on it
                        projects.erase(it);
                    x++;
                }
                
                for (int i = 0; i < projects.size(); i++)
                    cout << projects[i] << endl;
                cout << endl;
                break;
            }
        }
    }while(choice != 7);
    
    employee_file.close();
    
    cout << "Have a good day" << endl;
    
    return 0;
}

 
