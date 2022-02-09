from aligo import Aligo
import sys
import datetime

ali = Aligo(refresh_token=sys.argv[1])
share = ali.share_file(['5fdb5f561c7085c9fc0a42ef9965b157708c0876'],
                       share_name='临时文件',
                      share_pwd='963258',
                      expiration=str(datetime.datetime.now()+datetime.timedelta(days=1)),
                      description='自动分享')

print(share)
