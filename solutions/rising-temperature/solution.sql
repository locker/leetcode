select Weather.Id
from Weather
inner join Weather as t
on (Weather.recordDate = adddate(t.recordDate, interval 1 day) and
    Weather.temperature > t.temperature)
