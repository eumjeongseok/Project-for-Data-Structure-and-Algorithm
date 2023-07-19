#include <iostream>
#include <string>
#include <deque>

struct people {
    std::string name;
    char gender;
    char order;
};

int main() {
    int n;
    std::cin >> n;
    int meet = 0;
    std::deque<people> male_queue, female_queue, meet_male, meet_female,
        male_count, female_count;

    for (int i = 0; i < n; i++) {
        std::string name;
        int time;
        char gender;
        char order;
        std::cin >> time >> name >> gender >> order;

        people p = { name, gender, order };

        if (gender == 'm') {
            if (order == 'F') {
                male_queue.push_front(p);
            }
            else {
                male_queue.push_back(p);
            }
        }
        else {
            if (order == 'F') {
                female_queue.push_front(p);
            }
            else {
                female_queue.push_back(p);
            }
        }

        while (!male_queue.empty() && !female_queue.empty()) {
            meet_male.push_back(male_queue.front());
            meet_female.push_back(female_queue.front());
            male_count.push_back(male_queue.front());
            female_count.push_back(female_queue.front());
            male_queue.pop_front();
            female_queue.pop_front();

            meet = meet + 1;

            meet_male.pop_front();
            meet_female.pop_front();
        }
    }

    // Output remaining people
    while (!male_count.empty() || !female_count.empty())
    {
        std::cout << "Matched : " << male_count.front().name << " " << female_count.front().name << std::endl;
        male_count.pop_front();
        female_count.pop_front();
    }

    std::cout << meet << " " << male_queue.size() << " " << female_queue.size();
    return 0;
}
