
DigitTumbler {

    property DigitTumbler circularLink: null
    property int prevCurrentIndex: -1
    onCurrentIndexChanged: {
        if (circularLink !== null)
        {
            if (currentIndex === minDigit && prevCurrentIndex === maxDigit)
            {
                circularLink.increment()
            }
            else if (currentIndex === maxDigit && prevCurrentIndex === minDigit)
            {
                circularLink.decrement()
            }
        }

        prevCurrentIndex = currentIndex
    }
}
