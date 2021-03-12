select sname,city from S

select pname,color,weight from P

select jno from spj where sno='s1'

select p.pname, spj.qty from p,spj 
where p.pno=spj.pno and spj.jno='j2'

select distinct pno from spj where sno in 
(select sno from s where city='上海')

select jname from j,s,spj 
where j.jno=spj.jno and spj.sno=s.sno and s.city='上海'

update p set color='蓝' where color='红'

update spj set sno='s3' where sno='s5' and jno='j4' and pno='p6'

delete from spj from sno='s2'
delete from s from sno='s2'

insert into spj(sno,jno,pno.qty) values('s2','j6','p4',200)
insert into spj values('s2','j6','p4',200)