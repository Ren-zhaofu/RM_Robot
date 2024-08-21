function slBusOut = JointState(msgIn, slBusOut, varargin)
%#codegen
%   Copyright 2021-2022 The MathWorks, Inc.
    currentlength = length(slBusOut.Header);
    for iter=1:currentlength
        slBusOut.Header(iter) = bus_conv_fcns.ros.msgToBus.std_msgs.Header(msgIn.Header(iter),slBusOut(1).Header(iter),varargin{:});
    end
    slBusOut.Header = bus_conv_fcns.ros.msgToBus.std_msgs.Header(msgIn.Header,slBusOut(1).Header,varargin{:});
    maxlength = length(slBusOut.Name);
    recvdlength = length(msgIn.Name);
    currentlength = min(maxlength, recvdlength);
    if (max(recvdlength) > maxlength) && ...
            isequal(varargin{1}{1},ros.slros.internal.bus.VarLenArrayTruncationAction.EmitWarning)
        diag = MSLDiagnostic([], ...
                             message('ros:slros:busconvert:TruncatedArray', ...
                                     'Name', msgIn.MessageType, maxlength, max(recvdlength), maxlength, varargin{2}));
        reportAsWarning(diag);
    end
    slBusOut.Name_SL_Info.ReceivedLength = uint32(recvdlength);
    slBusOut.Name_SL_Info.CurrentLength = uint32(currentlength);
    for iter=1:currentlength
        recvlen = strlength(msgIn.Name(iter));
        maxlen = length(slBusOut.Name(iter).Data);
        curlen = min(recvlen, maxlen);
        if (max(recvlen) > maxlen) && ...
                isequal(varargin{1}{1},ros.slros.internal.bus.VarLenArrayTruncationAction.EmitWarning)
            diag = MSLDiagnostic([], ...
                                 message('ros:slros:busconvert:TruncatedArray', ...
                                         'Name', msgIn.MessageType, maxlen, max(recvdlength), maxlength, varargin{2}));
            reportAsWarning(diag);
        end
        slBusOut.Name(iter).Data_SL_Info.CurrentLength = uint32(curlen);
        slBusOut.Name(iter).Data_SL_Info.ReceivedLength = uint32(recvlen);
        slBusOut.Name(iter).Data(1:curlen) = uint8(char(msgIn.Name(iter)));
    end
    maxlength = length(slBusOut.Position);
    recvdlength = length(msgIn.Position);
    currentlength = min(maxlength, recvdlength);
    if (max(recvdlength) > maxlength) && ...
            isequal(varargin{1}{1},ros.slros.internal.bus.VarLenArrayTruncationAction.EmitWarning)
        diag = MSLDiagnostic([], ...
                             message('ros:slros:busconvert:TruncatedArray', ...
                                     'Position', msgIn.MessageType, maxlength, max(recvdlength), maxlength, varargin{2}));
        reportAsWarning(diag);
    end
    slBusOut.Position_SL_Info.ReceivedLength = uint32(recvdlength);
    slBusOut.Position_SL_Info.CurrentLength = uint32(currentlength);
    slBusOut.Position = double(msgIn.Position(1:slBusOut.Position_SL_Info.CurrentLength));
    if recvdlength < maxlength
    slBusOut.Position(recvdlength+1:maxlength) = 0;
    end
    maxlength = length(slBusOut.Velocity);
    recvdlength = length(msgIn.Velocity);
    currentlength = min(maxlength, recvdlength);
    if (max(recvdlength) > maxlength) && ...
            isequal(varargin{1}{1},ros.slros.internal.bus.VarLenArrayTruncationAction.EmitWarning)
        diag = MSLDiagnostic([], ...
                             message('ros:slros:busconvert:TruncatedArray', ...
                                     'Velocity', msgIn.MessageType, maxlength, max(recvdlength), maxlength, varargin{2}));
        reportAsWarning(diag);
    end
    slBusOut.Velocity_SL_Info.ReceivedLength = uint32(recvdlength);
    slBusOut.Velocity_SL_Info.CurrentLength = uint32(currentlength);
    slBusOut.Velocity = double(msgIn.Velocity(1:slBusOut.Velocity_SL_Info.CurrentLength));
    if recvdlength < maxlength
    slBusOut.Velocity(recvdlength+1:maxlength) = 0;
    end
    maxlength = length(slBusOut.Effort);
    recvdlength = length(msgIn.Effort);
    currentlength = min(maxlength, recvdlength);
    if (max(recvdlength) > maxlength) && ...
            isequal(varargin{1}{1},ros.slros.internal.bus.VarLenArrayTruncationAction.EmitWarning)
        diag = MSLDiagnostic([], ...
                             message('ros:slros:busconvert:TruncatedArray', ...
                                     'Effort', msgIn.MessageType, maxlength, max(recvdlength), maxlength, varargin{2}));
        reportAsWarning(diag);
    end
    slBusOut.Effort_SL_Info.ReceivedLength = uint32(recvdlength);
    slBusOut.Effort_SL_Info.CurrentLength = uint32(currentlength);
    slBusOut.Effort = double(msgIn.Effort(1:slBusOut.Effort_SL_Info.CurrentLength));
    if recvdlength < maxlength
    slBusOut.Effort(recvdlength+1:maxlength) = 0;
    end
end
