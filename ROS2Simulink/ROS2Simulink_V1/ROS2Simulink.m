

% 暂停3秒
pause(3)
t = 0;
% 通过之前创建的发布者cmdpub生成一个新的geometry_msgs/Twist类型的消息
while(1) 
    t = t + 1;
    cmdmsg = rosmessage(cmdpub);
    v = 2*sin(t);
    cmdmsg.Linear.X=0;
    cmdmsg.Angular.Z=0;
    % 发送
    send(cmdpub,cmdmsg)
end
