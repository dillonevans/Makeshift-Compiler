#ifndef CALL_FRAME_H
#define CALL_FRAME_H
#include <vector>
class CallFrame
{
private:

public:
    int basePointerOffset;
    CallFrame(int basePointerOffset);
};
#endif