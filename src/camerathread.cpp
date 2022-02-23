#include "camerathread.h"

CameraThread::CameraThread()
{
    up = false;
    recording = false;
    stopped = false;
    counter = 0;
    countFlag = true;
    rgb_chb = true;
    depth_chb = true;
    skelet_chb = true;
    writeflag = false;
    waitForWriting = false;
    rgbScale = 0.35;
    initialize();
}

CameraThread::~CameraThread()
{
    finalize();
}

void CameraThread::run()
{
    try{
        while(!stopped ){
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);

            update();
            draw();
            drawLines();
            if(recording){
                if(rgb_chb)
                    rgbVec.push_back(src.clone());
                if(depth_chb)
                    depthVec.push_back(scaleMat.clone());
                if(skelet_chb)
                    skeletVec.push_back(Body);
                recording = false;
                if( memInfo.ullAvailPhys < (536870912)){
                    emit record_pb();
                }
            }
            if(writeflag){
                waitForWriting = true;
                QString str = directory+"/Record"+QString::number(recordNumber);
                emit write(&rgbVec, &depthVec, &skeletVec, str);
                writeflag = false;
            }
            show();

            const int key = cv::waitKey( 10 );
            if( key == VK_ESCAPE ){
                break;
            }
    }
    }catch( std::exception& ex ){
        std::cout << ex.what() << std::endl;
    }
    stopped = false;
}


void CameraThread::stop()
{
    stopped = true;
    recording = false;
}



void CameraThread::getInformation(QString &dir, int recordNumber, bool rgb, bool depth, bool skelet)
{
    this->directory = dir;
    this->recordNumber = recordNumber;
    this->rgb_chb = rgb;
    this->depth_chb = depth;
    this->skelet_chb = skelet;
}


inline void CameraThread::getBodyIndex(const Joint & jnt, const ColorSpacePoint &color)
{
    switch (jnt.JointType) {
        case 0:
            Body.joint.X[0] = jnt.Position.X;
            Body.joint.Y[0] = jnt.Position.Y;
            Body.joint.Z[0] = jnt.Position.Z;
//            Body.joint.xColor[0] = color.X;
//            Body.joint.yColor[0] = color.Y;
            Body.joint.trackingState[0] = jnt.TrackingState;
            break;

        case 1:
            Body.joint.X[1] = jnt.Position.X;
            Body.joint.Y[1] = jnt.Position.Y;
            Body.joint.Z[1] = jnt.Position.Z;
            Body.joint.xColor[1] = color.X;
            Body.joint.yColor[1] = color.Y;
            Body.joint.trackingState[1] = jnt.TrackingState;
            break;

        case 2:
            Body.joint.X[2] = jnt.Position.X;
            Body.joint.Y[2] = jnt.Position.Y;
            Body.joint.Z[2] = jnt.Position.Z;
            Body.joint.xColor[2] = color.X;
            Body.joint.yColor[2] = color.Y;
            Body.joint.trackingState[2] = jnt.TrackingState;
            break;

        case 3:
            Body.joint.X[3] = jnt.Position.X;
            Body.joint.Y[3] = jnt.Position.Y;
            Body.joint.Z[3] = jnt.Position.Z;
            Body.joint.xColor[3] = color.X;
            Body.joint.yColor[3] = color.Y;
            Body.joint.trackingState[3] = jnt.TrackingState;
            break;

        case 4:
            Body.joint.X[4] = jnt.Position.X;
            Body.joint.Y[4] = jnt.Position.Y;
            Body.joint.Z[4] = jnt.Position.Z;
            Body.joint.xColor[4] = color.X;
            Body.joint.yColor[4] = color.Y;
            Body.joint.trackingState[4] = jnt.TrackingState;
            break;

        case 5:
            Body.joint.X[5] = jnt.Position.X;
            Body.joint.Y[5] = jnt.Position.Y;
            Body.joint.Z[5] = jnt.Position.Z;
            Body.joint.xColor[5] = color.X;
            Body.joint.yColor[5] = color.Y;
            Body.joint.trackingState[5] = jnt.TrackingState;
            break;

        case 6:
            Body.joint.X[6] = jnt.Position.X;
            Body.joint.Y[6] = jnt.Position.Y;
            Body.joint.Z[6] = jnt.Position.Z;
            Body.joint.xColor[6] = color.X;
            Body.joint.yColor[6] = color.Y;
            Body.joint.trackingState[6] = jnt.TrackingState;
            break;
        case 7:
            Body.joint.X[7] = jnt.Position.X;
            Body.joint.Y[7] = jnt.Position.Y;
            Body.joint.Z[7] = jnt.Position.Z;
            Body.joint.xColor[7] = color.X;
            Body.joint.yColor[7] = color.Y;
            Body.joint.trackingState[7] = jnt.TrackingState;
            break;

        case 8:
            Body.joint.X[8] = jnt.Position.X;
            Body.joint.Y[8] = jnt.Position.Y;
            Body.joint.Z[8] = jnt.Position.Z;
            Body.joint.xColor[8] = color.X;
            Body.joint.yColor[8] = color.Y;
            Body.joint.trackingState[8] = jnt.TrackingState;
            break;

        case 9:
            Body.joint.X[9] = jnt.Position.X;
            Body.joint.Y[9] = jnt.Position.Y;
            Body.joint.Z[9] = jnt.Position.Z;
            Body.joint.xColor[9] = color.X;
            Body.joint.yColor[9] = color.Y;
            Body.joint.trackingState[9] = jnt.TrackingState;
            break;

        case 10:
            Body.joint.X[10] = jnt.Position.X;
            Body.joint.Y[10] = jnt.Position.Y;
            Body.joint.Z[10] = jnt.Position.Z;
            Body.joint.xColor[10] = color.X;
            Body.joint.yColor[10] = color.Y;
            Body.joint.trackingState[10] = jnt.TrackingState;
            break;

        case 11:
            Body.joint.X[11] = jnt.Position.X;
            Body.joint.Y[11] = jnt.Position.Y;
            Body.joint.Z[11] = jnt.Position.Z;
            Body.joint.xColor[11] = color.X;
            Body.joint.yColor[11] = color.Y;
            Body.joint.trackingState[11] = jnt.TrackingState;
            break;

        case 12:
            Body.joint.X[12] = jnt.Position.X;
            Body.joint.Y[12] = jnt.Position.Y;
            Body.joint.Z[12] = jnt.Position.Z;
            Body.joint.xColor[12] = color.X;
            Body.joint.yColor[12] = color.Y;
            Body.joint.trackingState[12] = jnt.TrackingState;
            break;
        case 13:
            Body.joint.X[13] = jnt.Position.X;
            Body.joint.Y[13] = jnt.Position.Y;
            Body.joint.Z[13] = jnt.Position.Z;
            Body.joint.xColor[13] = color.X;
            Body.joint.yColor[13] = color.Y;
            Body.joint.trackingState[13] = jnt.TrackingState;
            break;

        case 14:
            Body.joint.X[14] = jnt.Position.X;
            Body.joint.Y[14] = jnt.Position.Y;
            Body.joint.Z[14] = jnt.Position.Z;
            Body.joint.xColor[14] = color.X;
            Body.joint.yColor[14] = color.Y;
            Body.joint.trackingState[14] = jnt.TrackingState;
            break;

        case 15:
            Body.joint.X[15] = jnt.Position.X;
            Body.joint.Y[15] = jnt.Position.Y;
            Body.joint.Z[15] = jnt.Position.Z;
            Body.joint.xColor[15] = color.X;
            Body.joint.yColor[15] = color.Y;
            Body.joint.trackingState[15] = jnt.TrackingState;
            break;

        case 16:
            Body.joint.X[16] = jnt.Position.X;
            Body.joint.Y[16] = jnt.Position.Y;
            Body.joint.Z[16] = jnt.Position.Z;
            Body.joint.xColor[16] = color.X;
            Body.joint.yColor[16] = color.Y;
            Body.joint.trackingState[16] = jnt.TrackingState;
            break;

        case 17:
            Body.joint.X[17] = jnt.Position.X;
            Body.joint.Y[17] = jnt.Position.Y;
            Body.joint.Z[17] = jnt.Position.Z;
            Body.joint.xColor[17] = color.X;
            Body.joint.yColor[17] = color.Y;
            Body.joint.trackingState[17] = jnt.TrackingState;
            break;

        case 18:
            Body.joint.X[18] = jnt.Position.X;
            Body.joint.Y[18] = jnt.Position.Y;
            Body.joint.Z[18] = jnt.Position.Z;
            Body.joint.xColor[18] = color.X;
            Body.joint.yColor[18] = color.Y;
            Body.joint.trackingState[18] = jnt.TrackingState;
            break;

        case 19:
            Body.joint.X[19] = jnt.Position.X;
            Body.joint.Y[19] = jnt.Position.Y;
            Body.joint.Z[19] = jnt.Position.Z;
            Body.joint.xColor[19] = color.X;
            Body.joint.yColor[19] = color.Y;
            Body.joint.trackingState[19] = jnt.TrackingState;
            break;

        case 20:
            Body.joint.X[20] = jnt.Position.X;
            Body.joint.Y[20] = jnt.Position.Y;
            Body.joint.Z[20] = jnt.Position.Z;
            Body.joint.xColor[20] = color.X;
            Body.joint.yColor[20] = color.Y;
            Body.joint.trackingState[20] = jnt.TrackingState;
            break;

        case 21:
            Body.joint.X[21] = jnt.Position.X;
            Body.joint.Y[21] = jnt.Position.Y;
            Body.joint.Z[21] = jnt.Position.Z;
            Body.joint.xColor[21] = color.X;
            Body.joint.yColor[21] = color.Y;
            Body.joint.trackingState[21] = jnt.TrackingState;
            break;

        case 22:
            Body.joint.X[22] = jnt.Position.X;
            Body.joint.Y[22] = jnt.Position.Y;
            Body.joint.Z[22] = jnt.Position.Z;
            Body.joint.xColor[22] = color.X;
            Body.joint.yColor[22] = color.Y;
            Body.joint.trackingState[22] = jnt.TrackingState;
            break;

        case 23:
            Body.joint.X[23] = jnt.Position.X;
            Body.joint.Y[23] = jnt.Position.Y;
            Body.joint.Z[23] = jnt.Position.Z;
            Body.joint.xColor[23] = color.X;
            Body.joint.yColor[23] = color.Y;
            Body.joint.trackingState[23] = jnt.TrackingState;
            break;

        case 24:
            Body.joint.X[24] = jnt.Position.X;
            Body.joint.Y[24] = jnt.Position.Y;
            Body.joint.Z[24] = jnt.Position.Z;
            Body.joint.xColor[24] = color.X;
            Body.joint.yColor[24] = color.Y;
            Body.joint.trackingState[24] = jnt.TrackingState;
            break;
        default:
            break;
        }
}

inline void CameraThread::drawLines()
{
    line(bodyMat, Point(Body.joint.xColor[3],Body.joint.yColor[3]),
            Point(Body.joint.xColor[2],Body.joint.yColor[2]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[2],Body.joint.yColor[2]),
            Point(Body.joint.xColor[20],Body.joint.yColor[20]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[20], Body.joint.yColor[20]),
            Point(Body.joint.xColor[8], Body.joint.yColor[8]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[8], Body.joint.yColor[8]),
            Point(Body.joint.xColor[9], Body.joint.yColor[9]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[9], Body.joint.yColor[9]),
            Point(Body.joint.xColor[10], Body.joint.yColor[10]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[10], Body.joint.yColor[10]),
            Point(Body.joint.xColor[24], Body.joint.yColor[24]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[10], Body.joint.yColor[10]),
            Point(Body.joint.xColor[11], Body.joint.yColor[11]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[11], Body.joint.yColor[11]),
            Point(Body.joint.xColor[23], Body.joint.yColor[23]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[20], Body.joint.yColor[20]),
            Point(Body.joint.xColor[4], Body.joint.yColor[4]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[4], Body.joint.yColor[4]),
            Point(Body.joint.xColor[5], Body.joint.yColor[5]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[5], Body.joint.yColor[5]),
            Point(Body.joint.xColor[6], Body.joint.yColor[6]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[6], Body.joint.yColor[6]),
            Point(Body.joint.xColor[22], Body.joint.yColor[22]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[6], Body.joint.yColor[6]),
            Point(Body.joint.xColor[7], Body.joint.yColor[7]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[7], Body.joint.yColor[7]),
            Point(Body.joint.xColor[21], Body.joint.yColor[21]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[20], Body.joint.yColor[20]),
            Point(Body.joint.xColor[1], Body.joint.yColor[1]), Scalar(255, 204, 0), 10, 16 );

    if(up)
        return;

    line(bodyMat, Point(Body.joint.xColor[1], Body.joint.yColor[1]),
            Point((Body.joint.xColor[12]+Body.joint.xColor[16])/2, (Body.joint.yColor[12]+Body.joint.yColor[16])/2),
            Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[12], Body.joint.yColor[12]),
            Point((Body.joint.xColor[12]+Body.joint.xColor[16])/2, (Body.joint.yColor[12]+Body.joint.yColor[16])/2),
            Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[16], Body.joint.yColor[16]),
            Point((Body.joint.xColor[12]+Body.joint.xColor[16])/2, (Body.joint.yColor[12]+Body.joint.yColor[16])/2),
             Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[16], Body.joint.yColor[16]),
            Point(Body.joint.xColor[17], Body.joint.yColor[17]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[17], Body.joint.yColor[17]),
            Point(Body.joint.xColor[18], Body.joint.yColor[18]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[18], Body.joint.yColor[18]),
            Point(Body.joint.xColor[19], Body.joint.yColor[19]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[12], Body.joint.yColor[12]),
            Point(Body.joint.xColor[13], Body.joint.yColor[13]), Scalar(255, 204, 0), 10, 16 );

    line(bodyMat, Point(Body.joint.xColor[13], Body.joint.yColor[13]),
            Point(Body.joint.xColor[14], Body.joint.yColor[14]), Scalar(255, 204, 0), 10, 16 );


    line(bodyMat, Point(Body.joint.xColor[14], Body.joint.yColor[14]),
            Point(Body.joint.xColor[15], Body.joint.yColor[15]), Scalar(255, 204, 0), 10, 16 );
}


// Initialize
void CameraThread::initialize()
{
    cv::setUseOptimized( true );

    // Initialize Sensor
    initializeSensor();

    // Initialize Color
    initializeColor();

    // Initialize Body
    initializeBody();

    // Initialize Depth
    initializeDepth();

    // Wait a Few Seconds until begins to Retrieve Data from Sensor ( about 2000-[ms] )
    std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
}

// Initialize Sensor
inline void CameraThread::initializeSensor()
{
    // Open Sensor
    ERROR_CHECK( GetDefaultKinectSensor( &kinect ) );

    ERROR_CHECK( kinect->Open() );

    // Check Open
    BOOLEAN isOpen = FALSE;
    ERROR_CHECK( kinect->get_IsOpen( &isOpen ) );
    if( !isOpen ){
        throw std::runtime_error( "failed IKinectSensor::get_IsOpen( &isOpen )" );
    }

    // Retrieve Coordinate Mapper
    ERROR_CHECK( kinect->get_CoordinateMapper( &coordinateMapper ) );
}

// Initialize Depth
inline void CameraThread::initializeDepth()
{
    // Open Depth Reader
    ComPtr<IDepthFrameSource> depthFrameSource;
    ERROR_CHECK(kinect->get_DepthFrameSource(&depthFrameSource));

    ERROR_CHECK(depthFrameSource->OpenReader(&depthFrameReader));

    // Retrieve Depth Description
    ComPtr<IFrameDescription> depthFrameDescription;
    ERROR_CHECK(depthFrameSource->get_FrameDescription(&depthFrameDescription));
    ERROR_CHECK(depthFrameDescription->get_Width(&depthWidth)); // 512
    ERROR_CHECK(depthFrameDescription->get_Height(&depthHeight)); // 424
    ERROR_CHECK(depthFrameDescription->get_BytesPerPixel(&depthBytesPerPixel)); // 2

    // Retrieve Depth Reliable Range
    UINT16 minReliableDistance;
    UINT16 maxReliableDistance;
    ERROR_CHECK(depthFrameSource->get_DepthMinReliableDistance(&minReliableDistance)); // 500
    ERROR_CHECK(depthFrameSource->get_DepthMaxReliableDistance(&maxReliableDistance)); // 4500

    // Allocation Depth Buffer
    depthBuffer.resize(depthWidth * depthHeight);
}


// Initialize Color
inline void CameraThread::initializeColor()
{
    // Open Color Reader
    ComPtr<IColorFrameSource> colorFrameSource;
    ERROR_CHECK( kinect->get_ColorFrameSource( &colorFrameSource ) );
    ERROR_CHECK( colorFrameSource->OpenReader( &colorFrameReader ) );

    // Retrieve Color Description
    ComPtr<IFrameDescription> colorFrameDescription;
    ERROR_CHECK( colorFrameSource->CreateFrameDescription( ColorImageFormat::ColorImageFormat_Bgra, &colorFrameDescription ) );
    ERROR_CHECK( colorFrameDescription->get_Width( &colorWidth ) ); // 1920
    ERROR_CHECK( colorFrameDescription->get_Height( &colorHeight ) ); // 1080
    ERROR_CHECK( colorFrameDescription->get_BytesPerPixel( &colorBytesPerPixel ) ); // 4

    // Allocation Color Buffer
    colorBuffer.resize( colorWidth * colorHeight * colorBytesPerPixel );
}

// Initialize Body
inline void CameraThread::initializeBody()
{
    // Open Body Reader
    ComPtr<IBodyFrameSource> bodyFrameSource;
    ERROR_CHECK( kinect->get_BodyFrameSource( &bodyFrameSource ) );
    ERROR_CHECK( bodyFrameSource->OpenReader( &bodyFrameReader ) );

    // Initialize Body Buffer
    Concurrency::parallel_for_each( bodies.begin(), bodies.end(), []( IBody*& body ){
        SafeRelease( body );
    } );

    // Color Table for Visualization
    colors[0] = cv::Vec3b( 255,   0,   0 ); // Blue
    colors[1] = cv::Vec3b(   0, 255,   0 ); // Green
    colors[2] = cv::Vec3b(   0,   0, 255 ); // Red
    colors[3] = cv::Vec3b( 255, 255,   0 ); // Cyan
    colors[4] = cv::Vec3b( 255,   0, 255 ); // Magenta
    colors[5] = cv::Vec3b(   0, 255, 255 ); // Yellow
}

// Finalize
void CameraThread::finalize()
{
    cv::destroyAllWindows();

    // Release Body Buffer
    Concurrency::parallel_for_each( bodies.begin(), bodies.end(), []( IBody*& body ){
        SafeRelease( body );
    } );

    // Close Sensor
    if( kinect != nullptr ){
        kinect->Close();
    }
}

// Update Data
void CameraThread::update()
{
    // Update Color
    updateColor();

    // Update Body
    updateBody();

    // Update Depth
    updateDepth();
}

// Update Depth
inline void CameraThread::updateDepth()
{
    // Retrieve Depth Frame
    ComPtr<IDepthFrame> depthFrame;
    const HRESULT ret = depthFrameReader->AcquireLatestFrame( &depthFrame );
    if( FAILED( ret ) ){
        return;
    }

    // Retrieve Depth Data
    ERROR_CHECK( depthFrame->CopyFrameDataToArray( static_cast<UINT>( depthBuffer.size() ), &depthBuffer[0] ) );
}

// Update Color
inline void CameraThread::updateColor()
{
    // Retrieve Color Frame
    ComPtr<IColorFrame> colorFrame;
    const HRESULT ret = colorFrameReader->AcquireLatestFrame( &colorFrame );
    if( FAILED( ret ) ){
        return;
    }

    // Convert Format ( YUY2 -> BGRA )
    ERROR_CHECK( colorFrame->CopyConvertedFrameDataToArray( static_cast<UINT>( colorBuffer.size() ), &colorBuffer[0], ColorImageFormat::ColorImageFormat_Bgra ) );

}

// Update Body
inline void CameraThread::updateBody()
{
    // Retrieve Body Frame
    ComPtr<IBodyFrame> bodyFrame;
    const HRESULT ret = bodyFrameReader->AcquireLatestFrame( &bodyFrame );
    if( FAILED( ret ) ){
        return;
    }

    // Release Previous Bodies
    Concurrency::parallel_for_each( bodies.begin(), bodies.end(), []( IBody*& body ){
        SafeRelease( body );
    } );

    // Retrieve Body Data
    ERROR_CHECK( bodyFrame->GetAndRefreshBodyData( static_cast<UINT>( bodies.size() ), &bodies[0] ) );


}

// Draw Data
void CameraThread::draw()
{
    drawColor();
    drawDepth();
    drawBody();
}

inline void CameraThread::drawDepth()
{
    // Create cv::Mat from Depth Buffer
    depthMat = cv::Mat(depthHeight, depthWidth, CV_16UC1, &depthBuffer[0]);
}

// Draw Color
inline void CameraThread::drawColor()
{
    // Create cv::Mat from Color Buffer
    colorMat = cv::Mat( colorHeight, colorWidth, CV_8UC4, &colorBuffer[0] );
    bodyMat = colorMat.clone();
    cv::resize( bodyMat, src, cv::Size(), rgbScale, rgbScale);
}

// Draw Body
inline void CameraThread::drawBody()
{
    // Draw Body Data to Color Data
    Concurrency::parallel_for( 0, BODY_COUNT, [&]( const int count ){
        const ComPtr<IBody> body = bodies[count];
        if( body == nullptr ){
            return;
        }

        // Check Body Tracked
        BOOLEAN tracked = FALSE;
        ERROR_CHECK( body->get_IsTracked( &tracked ) );
        if( !tracked ){
            return;
        }

        // Retrieve Joints
        std::array<Joint, JointType::JointType_Count> joints;
        ERROR_CHECK( body->GetJoints( static_cast<UINT>( joints.size() ), &joints[0] ) );

        Concurrency::parallel_for_each( joints.begin(), joints.end(), [&]( const Joint& joint ){
            // Check Joint Tracked
            if( joint.TrackingState == TrackingState::TrackingState_NotTracked ){
                return;
            }

            // Draw Joint Position
            drawEllipse( bodyMat, joint, 10, colors[count] );

            // Draw Left Hand State
            if( joint.JointType == JointType::JointType_HandLeft ){
                HandState handState;
                TrackingConfidence handConfidence;
                ERROR_CHECK( body->get_HandLeftState( &handState ) );
                ERROR_CHECK( body->get_HandLeftConfidence( &handConfidence ) );

                drawHandState( bodyMat, joint, handState, handConfidence );
            }

            // Draw Right Hand State
            if( joint.JointType == JointType::JointType_HandRight ){
                HandState handState;
                TrackingConfidence handConfidence;
                ERROR_CHECK( body->get_HandRightState( &handState ) );
                ERROR_CHECK( body->get_HandRightConfidence( &handConfidence ) );

                drawHandState( bodyMat, joint, handState, handConfidence );
            }
        } );
    } );


}

// Draw Ellipse
inline void CameraThread::drawEllipse( cv::Mat& image, const Joint& joint, const int radius, const cv::Vec3b& color, const int thickness )
{
    if( image.empty() ){
        return;
    }
    if(up){
        if( (joint.JointType == 12) | (joint.JointType == 16) |
                (joint.JointType == 13) | (joint.JointType == 17) | (joint.JointType == 14) |
                (joint.JointType == 18) | (joint.JointType == 15) | (joint.JointType == 19) )
            return;
    }

    // Convert Coordinate System and Draw Joint
    ColorSpacePoint colorSpacePoint;
    ERROR_CHECK( coordinateMapper->MapCameraPointToColorSpace( joint.Position, &colorSpacePoint ) );
    const int x = static_cast<int>( colorSpacePoint.X + 0.5f );
    const int y = static_cast<int>( colorSpacePoint.Y + 0.5f );
    getBodyIndex(joint, colorSpacePoint);

    if ((0 <= x) && (x < image.cols) && (0 <= y) && (y < image.rows)) {
        cv::circle(image, cv::Point(x, y), radius, static_cast<cv::Scalar>(color), thickness, cv::LINE_AA);
    }
}

// Draw Hand State
inline void CameraThread::drawHandState( cv::Mat& image, const Joint& joint, HandState handState, TrackingConfidence handConfidence )
{
    if( image.empty() ){
        return;
    }

    // Check Tracking Confidence
    if( handConfidence != TrackingConfidence::TrackingConfidence_High ){
        return;
    }

    // Draw Hand State
    const int radius = 75;
    const cv::Vec3b blue = cv::Vec3b( 128, 0, 0 ), green = cv::Vec3b( 0, 128, 0 ), red = cv::Vec3b( 0, 0, 128 );
    switch( handState ){
        // Open
        case HandState::HandState_Open:
            drawEllipse( image, joint, radius, green, 5 );
            break;
        // Close
        case HandState::HandState_Closed:
            drawEllipse( image, joint, radius, red, 5 );
            break;
        // Lasso
        case HandState::HandState_Lasso:
            drawEllipse( image, joint, radius, blue, 5 );
            break;
        default:
            break;
    }
}

// Show Data
void CameraThread::show()
{
    // Show Body
    showBody();

    // Show Depth
    showDepth();
}

// Show Body
inline void CameraThread::showBody()
{
    if( colorMat.empty() ){
        return;
    }

    // Resize Image
    const double scale = 0.5;
    cv::resize( bodyMat, resizeMat, cv::Size(), scale, scale );
    if(waitForWriting)
        putText(resizeMat, "Writinng Information, Please Wait :)", cvPoint(resizeMat.cols/4, resizeMat.rows/2),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(0,0,255), 2, CV_AA);
    // Show Image
    cv::imshow( "Body", resizeMat );

}


inline void CameraThread::showDepth()
{
    if (depthMat.empty()) {
        return;
    }

    // Scaling ( 0-8000 -> 255-0 )
    depthMat.convertTo(scaleMat, CV_8U, -255.0 / 8000.0, 255.0);
    //cv::applyColorMap( scaleMat, scaleMat, cv::COLORMAP_BONE );
    // Show Image
    cv::imshow("Depth", scaleMat);
}


void CameraThread::cameraStartSlot()
{
    if(!recording)
        recording = true;
    if(!countFlag)
        countFlag = true;
    else
        counter++;
}

void CameraThread::cameraStopSlot()
{
    writeflag = true;
    recording = false;
    countFlag = false;
    counter = 0;
}

void CameraThread::stopWrite()
{
    rgbVec.clear();
    depthVec.clear();
    skeletVec.clear();
    waitForWriting = false;
}

void CameraThread::showUpper(bool checked)
{
    up = checked;
}
