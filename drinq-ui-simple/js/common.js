function updateTimeSinceLastDrink(diff_secs) {
    const preamble = qsTr("last consumed drink: ")
    const suffix = qsTr(" ago")

    if(diff_secs === -1)
    {
        return ""
    }
    else if(diff_secs < 60)
    {
        return preamble + qsTr("less than a minute") + suffix

    }
    else if(diff_secs < 3600)
    {
        const diff_mins = Math.floor(diff_secs / 60)
        const mins_string = (diff_mins > 1 ? diff_mins + qsTr(" minutes") : qsTr("1 minute"))
        return preamble + mins_string + suffix
    }
    else if(diff_secs < 86400)
    {
        const diff_hours = Math.floor(diff_secs / 3600)
        const diff_mins = Math.floor((diff_secs - (diff_hours * 3600)) / 60)

        const hours_string = (diff_hours > 1 ? diff_hours + qsTr(" hours ") : qsTr("1 hour"))
        const mins_string = (diff_mins == 0 ? "" : diff_mins == 1 ? qsTr(" 1 minute") : diff_mins + qsTr(" minutes"))

        return preamble + hours_string + mins_string + suffix
    }
    else
    {
        const diff_days = Math.floor(diff_secs / 86400)
        const diff_hours = Math.floor((diff_secs - (diff_days * 86400)) / 3600)
        const diff_mins = Math.floor((diff_secs - (diff_days * 86400) - (diff_hours * 3600)) / 60)

        const days_string =  (diff_days > 1 ? diff_days + qsTr(" days ") : qsTr("1 day"))
        const hours_string = (diff_hours > 1 ? diff_hours + qsTr(" hours ") : qsTr("1 hour"))
        const mins_string = (diff_mins == 0 ? "" : diff_mins == 1 ? qsTr(" 1 minute") : diff_mins + qsTr(" minutes"))

        return preamble + days_string + hours_string + mins_string + suffix
    }
}
