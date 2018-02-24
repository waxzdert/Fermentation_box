boolean switch;

void setup()
{
  switch = false;
  pinMode(3, OUTPUT);
}


void loop()
{
  if (switch) {
    digitalWrite(3, HIGH);
    switch = false;

  } else {
    digitalWrite(3, LOW);
    switch = true;
  }
  delay(2000);
}
