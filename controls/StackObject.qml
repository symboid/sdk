
import QtQuick 2.12

QtObject {
    property int length: 0
    property var stack: []
    function push(screen)
    {
        stack.push(screen)
        length++
    }
    function pop()
    {
        var screen = null
        if (length > 0) {
            screen = stack.pop()
            length--
        }
        return screen
    }
    function cleanup()
    {
        for (var s = 0; s < stack.length; ++s)
        {
            var screen = stack[s]
            screen.destroy()
        }
        stack = []
        length = 0
    }
}
