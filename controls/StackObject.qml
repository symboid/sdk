
import QtQuick 2.12

QtObject {
    property int depth: 0
    property var stack: []
    function push(screen)
    {
        stack.push(screen)
        depth++
    }
    function pop()
    {
        var screen = null
        if (depth > 0) {
            screen = stack.pop()
            depth--
        }
        return screen
    }
    function cleanup()
    {
        for (var s = 0; s < stack.depth; ++s)
        {
            var screen = stack[s]
            screen.destroy()
        }
        stack = []
        depth = 0
    }
}
