function updateTimeSinceLastDrink(diff_secs) {
    if(diff_secs === -1)
    {
        return ""
    }
    else if(diff_secs <= 60)
    {
        return qsTr("last consumed drink: less than a minute ago")
    }
    else if(diff_secs <= 3600)
    {
        const diff_mins = Math.floor(diff_secs / 60)
        return qsTr("last consumed drink: ") + diff_mins + qsTr(" minutes ago")
    }
    else if(diff_secs <= 86400)
    {
        const diff_hours = Math.floor(diff_secs / 3600)
        const diff_mins = Math.floor((86400 - diff_secs) / 60)
        return qsTr("last consumed drink: ")
                                         + diff_hours + qsTr(" hour ")
                                         + diff_mins + qsTr(" minutes ago ")
    }
    else
    {
        const diff_days = Math.floor(diff_secs / 86400)
        const diff_hours = Math.floor((diff_secs - (diff_days * 86400)) / 3600)
        const diff_mins = Math.floor((diff_secs - (diff_days * 86400) - (diff_hours * 3600)) / 60)
        return qsTr("last consumed drink: ")
                                         + diff_days + qsTr(" days ")
                                         + diff_hours + qsTr(" hours ")
                                         + diff_mins + qsTr(" minutes ago ")
    }
}
