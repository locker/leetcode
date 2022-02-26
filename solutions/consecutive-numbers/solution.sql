select distinct t.num as ConsecutiveNums from (
    select t1.id, t1.num, count(*) as cnt
    from Logs as t1
    join Logs as t2
    on t1.num = t2.num and (t1.id + 1 = t2.id or t1.id + 2 = t2.id)
    group by t1.id) as t
where t.cnt > 1
