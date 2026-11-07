#include "process.h"
#include "Student.h"

static bool byName(const Student& a, const Student& b) {
    if (a.getName() == b.getName()) {
        return a.getSurname() < b.getSurname();
    }
    return a.getName() < b.getName();
}

static bool isFailed(const Student &s) { return s.resultsAverage() <  PASS_MARK; }
static bool isPassed(const Student &s) { return s.resultsAverage() >= PASS_MARK; }

const char *strategyName(Strategy s) {
    switch (s) {
        case Strategy::Copy:          return "S1 copy (loop)";
        case Strategy::Move:          return "S2 move+erase (loop)";
        case Strategy::CopyAlgo:      return "S1 remove_copy_if/copy_if";
        case Strategy::MoveAlgo:      return "S2 stable_partition";
        case Strategy::PartitionSort: return "S2 partition+sort";
        case Strategy::FindIfSplice:  return "S2 find_if+splice";
    }
    return "?";
}

// std::sort needs random access; std::list brings its own sort().
template <class C>
static void sortAny(C &Group) {
    if constexpr (is_same_v<C, list<Student>>) Group.sort(byName);
    else                                       sort(Group.begin(), Group.end(), byName);
}

void sortStudents(Container &Group) {
    sortAny(Group);
}

// ---------------------------------------------------------------- Strategy 1
// Original loop, but copying: "all" keeps everybody.
static void splitCopy(const Container &all, Container &passed, Container &failed) {
    for (const Student &s : all) {
        (isPassed(s) ? passed : failed).push_back(s);
    }
}

// Same with <algorithm>: remove_copy_if copies everything that is NOT failed (= passed).
static void splitCopyAlgo(const Container &all, Container &passed, Container &failed) {
    remove_copy_if(all.begin(), all.end(), back_inserter(passed), isFailed);
    copy_if(all.begin(), all.end(), back_inserter(failed), isFailed);
}

// ---------------------------------------------------------------- Strategy 2
// Failed students are moved out of "all" and erased one by one.
// vector / deque have to shift every following element on each erase.
static void splitMove(Container &all, Container &failed) {
    for (auto it = all.begin(); it != all.end(); ) {
        if (isFailed(*it)) {
            failed.push_back(move(*it));
            it = all.erase(it);
        } else {
            ++it;
        }
    }
}

// After a partition the failed students are the tail [mid, end).
// They are moved to "failed" and the tail is cut off ONCE.
template <class C>
static void moveTail(C &all, typename C::iterator mid, C &failed) {
    if constexpr (is_same_v<C, list<Student>>) {
        failed.splice(failed.end(), all, mid, all.end());   // relinks nodes, no copies
    } else {
        failed.insert(failed.end(), make_move_iterator(mid), make_move_iterator(all.end()));
        all.erase(mid, all.end());
    }
}

// stable_partition keeps the (already sorted) order inside both groups.
static void splitMoveAlgo(Container &all, Container &failed) {
    auto mid = stable_partition(all.begin(), all.end(), isPassed);
    moveTail(all, mid, failed);
}

// partition is cheaper (no buffer, no order) - the groups are sorted afterwards.
static void splitPartition(Container &all, Container &failed) {
    auto mid = partition(all.begin(), all.end(), isPassed);
    moveTail(all, mid, failed);
}

// std::list only: find_if finds the next failed student and splice relinks that node
// into "failed" - no student is copied or moved, and nothing is shifted.
// (Other containers have no splice, so this strategy is not available for them.)
template <class C>
static void findIfSplice(C &all, C &failed) {
    if constexpr (is_same_v<C, list<Student>>) {
        auto it = all.begin();
        while ((it = find_if(it, all.end(), isFailed)) != all.end()) {
            auto following = std::next(it);
            failed.splice(failed.end(), all, it);
            it = following;
        }
    } else {
        splitMoveAlgo(all, failed);     // not used: Test skips this strategy for them
    }
}

void splitStudents(Strategy s, Container &all, Container &passed, Container &failed) {
    switch (s) {
        case Strategy::Copy:          splitCopy(all, passed, failed);     break;
        case Strategy::CopyAlgo:      splitCopyAlgo(all, passed, failed); break;
        case Strategy::Move:          splitMove(all, failed);             passed = move(all); all.clear(); break;
        case Strategy::MoveAlgo:      splitMoveAlgo(all, failed);         passed = move(all); all.clear(); break;
        case Strategy::PartitionSort: splitPartition(all, failed);        passed = move(all); all.clear(); break;
        case Strategy::FindIfSplice:  findIfSplice(all, failed);          passed = move(all); all.clear(); break;
    }
}
