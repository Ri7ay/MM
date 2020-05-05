#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include<set>
#include <exception>
#include <limits>
#include <utility>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return team.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        team[person][TaskStatus::NEW]++;
    }

    void RemoveZeros(TasksInfo& tasks_info) {
        // Соберём те статусы, которые нужно убрать из словаря
        vector<TaskStatus> statuses_to_remove;
        for (const auto& task_item : tasks_info) {
            if (task_item.second == 0) {
                statuses_to_remove.push_back(task_item.first);
            }
        }
        for (const TaskStatus status : statuses_to_remove) {
            tasks_info.erase(status);
        }
    }
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo refresh = {{TaskStatus::NEW, 0}, {TaskStatus::IN_PROGRESS, 0}, {TaskStatus::TESTING, 0},
                             {TaskStatus::DONE, 0},}, not_refresh;
        while (team[person][TaskStatus::NEW] != 0 && task_count != 0) {
            team[person][TaskStatus::NEW]--;
            refresh[TaskStatus::IN_PROGRESS]++;
            task_count--;
        }
        not_refresh[TaskStatus::NEW] = team[person][TaskStatus::NEW];
        while (team[person][TaskStatus::IN_PROGRESS] != 0  && task_count != 0) {
            team[person][TaskStatus::IN_PROGRESS]--;
            refresh[TaskStatus::TESTING]++;
            task_count--;
        }
        not_refresh[TaskStatus::IN_PROGRESS] = team[person][TaskStatus::IN_PROGRESS];
        while (team[person][TaskStatus::TESTING] != 0 && task_count != 0) {
            team[person][TaskStatus::TESTING]--;
            refresh[TaskStatus::DONE]++;
            task_count--;
        }
        not_refresh[TaskStatus::TESTING] = team[person][TaskStatus::TESTING];
        //not_refresh[TaskStatus::DONE] = team[person][TaskStatus::DONE];
        team[person][TaskStatus::NEW] = refresh[TaskStatus::NEW] + not_refresh[TaskStatus::NEW];
        team[person][TaskStatus::IN_PROGRESS] = refresh[TaskStatus::IN_PROGRESS] + not_refresh[TaskStatus::IN_PROGRESS];
        team[person][TaskStatus::TESTING] = refresh[TaskStatus::TESTING] + not_refresh[TaskStatus::TESTING];
        team[person][TaskStatus::DONE] += refresh[TaskStatus::DONE];
        not_refresh[TaskStatus::DONE] = 0;
        RemoveZeros(refresh);
        RemoveZeros(not_refresh);
        return make_pair(refresh, not_refresh);
    }

private:
    map<string, TasksInfo> team;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i <2; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 1);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    tasks.AddNewTask("Ivan");
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 3);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    return 0;
}


