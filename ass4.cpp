#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <string>

using namespace std;
class ReaderWriter
{
private:
    mutex mtx;
    condition_variable cv;
    int readers = 0,
        writers = 0;
    bool is_writing = false;

public:
    void startRead()
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]
                { return !is_writing; });
        ++readers;
    }
    void endRead()
    {
        unique_lock<mutex> lock(mtx);
        if (--readers == 0)
        {
            cv.notify_all();
        }
    }
    void startWrite()
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]
                { return readers == 0 && !is_writing; });
        ++writers;
        is_writing = true;
    }
    void endWrite()
    {
        unique_lock<mutex> lock(mtx);
        --writers;
        is_writing = false;
        cv.notify_all();
    }

    bool canAddWriter()
    {
        lock_guard<mutex> lock(mtx);
        return readers == 0 && !is_writing;
    }
    bool canDeleteWriter()
    {
        lock_guard<mutex> lock(mtx);
        return writers > 0;
    }
    bool canDeleteReader()
    {
        lock_guard<mutex> lock(mtx);
        return readers > 0;
    }
    bool canAddReader()
    {
        lock_guard<mutex> lock(mtx);
        return !is_writing;
    }
};
ReaderWriter rw;
void reader(int id)
{
    rw.startRead();
    cout << "Reader " << id << " is reading." << endl;
    // Simulating reading
    this_thread::sleep_for(chrono::milliseconds(1000));
    rw.endRead();
}
void writer(int id)
{
    rw.startWrite();
    cout << "Writer " << id << " is writing." << endl;
    // Simulating writing
    this_thread::sleep_for(chrono::milliseconds(2000));
    rw.endWrite();
}
int main()
{
    vector<thread> readers, writers;
    string input;
    while (true)
    {
        cout << "Choose an option:\n 1. Add reader\n 2. Delete reader\n 3. Add writer\n 4.Delete writer\n 5. Exit\n";
        cin >> input;
        switch (stoi(input))
        {
        case 1:
            if (rw.canAddReader())
            {
                rw.startRead();
                cout << "Reader added successfully." << endl;
                readers.emplace_back(reader, readers.size() + 1);
            }
            else
            {
                cout << "Cannot add reader at the moment... \n Cannot add reader while writer is writing " << endl;
            }
            break;
        case 2:
            if (rw.canDeleteReader())
            {
                readers.back().join();
                rw.endRead();
                cout << "Reader deleted successfully." << endl;
                readers.pop_back();
            }
            else
            {
                cout << "No reader to delete." << endl;
            }
            break;
        case 3:
            if (rw.canAddWriter())
            {
                rw.startWrite();
                cout << "Writer added successfully." << endl;
                writers.emplace_back(writer, writers.size() + 1);
            }
            else
            {
                cout << "Cannot add writer at the moment.... \n Cannot add writer whilereaders are reading or another writer is writing." << endl;
            }
            break;
        case 4:
            if (rw.canDeleteWriter())
            {
                rw.endWrite();
                writers.back().join();
                cout << "Writer deleted successfully." << endl;
                writers.pop_back();
            }
            else
            {
                cout << "No writer to delete." << endl;
            }
            break;
        case 5:
            for (auto &readerThread : readers)
                readerThread.join();
            for (auto &writerThread : writers)
                writerThread.join();
            return 0;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }
}