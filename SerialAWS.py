import serial
import time
import boto3


def main():
    isranOnce = False
    

    while(True):
        # Set up Serial connection
        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)  # Replace with COM port on Windows, e.g., 'COM3'
        time.sleep(2)  # Wait for Arduino to initialize
        linetes = ser.readline().decode().strip()
        print(linetes)

       

        if("Finished Level" in linetes and not isranOnce):
            isranOnce = True

             # Setup AWS S3 via Boto
            s3 = boto3.client('s3')
            s3resource = boto3.resource('s3')

            #Getting the buckets and setting up variables
            bucket_name = 'testingarduino'
            s3_key = 'submissions/Highscore.txt'
            bucket = s3resource.Bucket(bucket_name)
            body = None

            for obj in bucket.objects.all():
                if(obj.key == s3_key or obj.key == "submissions/Highscore"):
                    body = obj.get()['Body'].read().decode('utf-8')
            if(body == None):
                return

            # Extract scores
            scores = []
            with open('scores.txt', 'r') as f:
                bodyl = f.read().split(" ")
                for i in range(0, len(bodyl)):
                    try:
                        scores.append(int(bodyl[i]))
                    except Exception:
                        pass
            

            for line in body.splitlines():
                for val in line.split(","):
                    val = val.strip()
                    if val.lower() != "highscore" and val != "":
                        try:
                            scores.append(int(val))
                        except ValueError:
                            pass  # ignore invalid numbers

            # Get new score
            try:
                new_score = int(linetes.strip().split(" ")[-1])
                for i in range(0,len(scores)):
                    if(new_score < scores[i]):
                        scores.insert(i-1, new_score)
                scores.append(new_score)
            except ValueError:
                print("Invalid high score:", linetes)
                return

            # Sort and write
            scores = sorted(scores)

            with open('scores.txt', 'w') as f:
                f.write("Highscore: " + ", ".join(map(str, scores)) + "\n")

            print("Highscore:", scores)
                


            # Upload the file to S3
            with open('scores.txt', 'rb') as f:
                s3.upload_fileobj(f, bucket_name, s3_key)

            print("Data uploaded to S3!")
            ser.close()
            return


if __name__ == "__main__":
    try:
        main()
    except EOFError:
        print("Something went wrong, are you sure that the board is connected")