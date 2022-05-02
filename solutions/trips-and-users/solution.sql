select Trips.request_at as Day,
    round(count(if(Trips.status <> 'completed', 1, null)) / count(*), 2) as 'Cancellation Rate'
from Trips
join Users as Clients on Trips.client_id = Clients.users_id and Clients.banned <> 'Yes'
join Users as Drivers on Trips.driver_id = Drivers.users_id and Drivers.banned <> 'Yes'
where request_at >= '2013-10-01' and request_at <= '2013-10-03'
group by request_at order by request_at
