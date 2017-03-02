#ifndef TEST_H
#define TEST_H

#include <vector>
#include <string>
#include "../utils.h"
#include "database.h"

void performTest(Database *db)
{
  // Create table
  db->execute("DROP TABLE IF EXISTS test");
  db->execute("CREATE TABLE test(id INT PRIMARY KEY, name TEXT)");

  // Insert Items
  Log("Preparing first statement");
  auto pstmt = db->prepare("INSERT INTO test(id, name) VALUES (?, ?)");
  Log("prepared the first statement");
  std::vector<std::string> values = {"King", "Steph", "Azba"};
  for (int i = 0; i < (signed)values.size(); i++) {
    Log("Inserting int", i);
    pstmt->setInt(1, i);
    Log("Inserting string");
    pstmt->setString(2, values[i].c_str());
    Log("Executing update");
    pstmt->executeUpdate();
  }

  // Fetch items
  Log("Preparing last statement");
  pstmt = db->prepare("SELECT id,name FROM test ORDER BY id ASC");
  Log("executing query");
  auto resp = pstmt->executeQuery();
  //Log("Preparing last statement");
  //resp->afterLast();
  Log("Ierating results");
  while (resp->next()) {
    Log("Geting results");
    Log("id:", resp->getInt(1), "name:", resp->getString(2));
  }

  // Delete table when done
  Log("cleaning up");
  db->execute("DROP TABLE IF EXISTS test");
}

#endif // !TEST_H