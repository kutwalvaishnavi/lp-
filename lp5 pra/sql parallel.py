import sqlite3
import concurrent.futures
import time

def exe_sql_qry(query):

    try:
        conn=sqlite3.connect('mydb.db')

        cursor=conn.cursor()

        cursor.execute(query)
        if query.strip().lower().startswith('select'):
            result=cursor.fetchall()

        else:
            conn.commit()
            result='Query Executed...'
        

        
        conn.close()

        return result

    except Exception as e:
        return f'error occured {str(e)}'

queries=[
    #"CREATE TABLE users(id number primary key,name varchar,mono number(10));",
    #"INSERT INTO USERS VALUES(01,'SANKET',90000000);",
    #"INSERT INTO USERS VALUES(02,'TANMAY',80000000);",
    #"INSERT INTO USERS VALUES(03,'SANKET',90000000);",
    #"INSERT INTO USERS VALUES(04,'SANKET',90000000);",
    #"INSERT INTO USERS VALUES(05,'SANKET',90000000);",
    
    "SELECT * from users;",
    #"SELECT * from users;",
    #"SELECT * from users;",
    #"SELECT * from users;",
    #"SELECT * from users;",

    ]
s1time=time.time()
with concurrent.futures.ThreadPoolExecutor() as executor:
    results1=list(executor.map(exe_sql_qry,queries))
e1time=time.time()
s2time=time.time()
results2=list(map(exe_sql_qry,queries))
e2time=time.time()
for result in results1:
    
    print(result)
for result in results2:
    print(result)

print('total time1',e1time-s1time)
print('total time2',e2time-s2time)
